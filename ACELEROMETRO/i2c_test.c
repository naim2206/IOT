#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <string.h>

#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include <arpa/inet.h>


#define PORT 8080
#define TIMES 5

#define SENSOR_ADDR     0x18

static int read_registers(int fd, uint8_t addr, uint8_t reg, uint8_t * buff, uint8_t size) {
    
    struct i2c_rdwr_ioctl_data msgs[1];
    struct i2c_msg i2cmsg[2];
    int ret;
    uint8_t register_address = reg | (1 << 7);

    /*Send WR Register Address*/
    i2cmsg[0].addr = addr;
    i2cmsg[0].flags = 0;
    i2cmsg[0].len = 1;
    i2cmsg[0].buf = &register_address;

    i2cmsg[1].addr = addr;
    i2cmsg[1].flags = I2C_M_RD; 
    i2cmsg[1].len = size;
    i2cmsg[1].buf = buff;

    msgs[0].msgs = i2cmsg;
    msgs[0].nmsgs = 2;

    if ( (ret = ioctl(fd, I2C_RDWR, msgs)) < 0) {
        perror("ERROR in I2C_RDWR");
        close(fd);
        return -1;
    }

    return 0;
}


static int write_registers(int fd, uint8_t addr, uint8_t reg, uint8_t * buff, uint8_t size) {

    char buffer[size + 1];

    if ( ioctl(fd, I2C_SLAVE, addr) < 0) {
        printf("ERROR in I2C_SLAVE\n");
        close(fd);
        return -1;
    }

    buffer[0] = reg;
    memcpy(&buffer[1], buff, size);

    /*Set Registers*/
    if (write(fd, &buffer, size + 1) < 0 ){
        perror("ERROR in WRITE\n");
        return -1;
    }
        
    return 0;
}


int main(int argc, char * argv[]) {

    

    uint8_t x_l,x_h,y_l,y_h,z_l,z_h ,write = 0x1f;
    uint16_t x = 0,y = 0,z = 0;
    int fd = open("/dev/i2c-1", O_RDWR);
    int writing = write_registers(fd, SENSOR_ADDR,0x20, &write, sizeof(write));


    int socket_connection = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    memset(&server, 0 , sizeof(server));

    
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(socket_connection, (struct  sockaddr *)&server, sizeof(server) );
    ret = listen(socket_connection, 10);

    for(int i = 0; i < TIMES; i++){
        read_registers(fd, SENSOR_ADDR, 0x28, &x_l, sizeof(x_l));
        read_registers(fd, SENSOR_ADDR, 0x29, &x_h, sizeof(x_h));
        
        read_registers(fd, SENSOR_ADDR, 0x2a, &y_l, sizeof(y_l));
        read_registers(fd, SENSOR_ADDR, 0x2b, &y_h, sizeof(y_h));
                
        read_registers(fd, SENSOR_ADDR, 0x2c, &z_l, sizeof(z_l));
        read_registers(fd, SENSOR_ADDR, 0x2d, &z_h, sizeof(z_h));


        x |= x_h;
        x = x << 8;
        x |= x_l;

        y |= y_h;
        y = y << 8;
        y |= y_l;

        z |= z_h;
        z = z << 8;
        z |= z_l;


        char arr[50];
        snprintf(arr, sizeof(arr), "x: %.2fg, y: %.2fg, z: %.2fg\n", (float)x, (float)y,(float)z);
        int sock = accept(socket_connection, (struct sockaddr *)NULL, NULL);
        printf("%s", arr);

        ret = send(sock, arr, sizeof(arr), 0);
        ret = close(sock);

    }

    ret = close(socket_connection);
    return 0;
    
    if (ret < 0)
        return -1;

    

    return 0;
}
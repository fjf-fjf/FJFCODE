 #ifndef A__TEST_HA_TEST_H
 #define A__TEST_HA_TEST_H
int lcd_fd;
int *lcd_mp;
int ts_fd;



void update_video(int new_value);






void open_device();
void close_device();





#endif
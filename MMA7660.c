void init_MMA7660()
{
 i2c_start();
 i2c_write(0x98);
 i2c_write(0x07);
 i2c_write(0x01);
 i2c_stop();
}
u8 read_MMA7660(u8 reg)
{
 u8 data;
 i2c_start();
 i2c_write(0x98);
 i2c_write(reg);
 i2c_restart();
 i2c_write(0x99);
 data=i2c_nack();
 if(data>31)
 {
  data=data-64;
 }
 i2c_stop();
 delay_ms(10);
 return data;
}



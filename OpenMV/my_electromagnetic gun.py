# ******************************************************************************
#   * @file   my_electromagnetic gun.py
#   * @author jiangtao
#   * @date   2021.6.7
#   * @brief  This file includes the measurement of Red circle target and a interrupt
#   * @attention This file should be used for  Laboratory task.
# ******************************************************************************
import sensor, image, time , pyb
from pyb import Servo #舵机控制 于另一块板子使用 故openmv并未使用该功能
from pyb import UART
from pyb import Pin



############################################################ 一些openmv功能初始化
#将蓝灯赋值给变量led
led = pyb.LED(3)       # Red LED = 1, Green LED = 2, Blue LED = 3, IR LEDs = 4.
pin1 = Pin('P1', Pin.OUT_PP, Pin.PULL_NONE)
pin1.low()             #对于openmv H7 的蓝灯闪烁 目的是观察是否传输数据
uart = UART(3, 115200)  #串口使用
sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.
############################################################

##########################################################一些函数
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob=blob
            max_size = blob.pixels()
    return max_blob

def find_length(blobs):   #测距
        img.draw_rectangle(b[0:4]) # rect
        img.draw_cross(b[5], b[6]) # cx, cy
        Lm = (b[2]+b[3])/2
        leng = 5200/Lm
        return int(leng)
#############################################################

##############################################一些基础变量
#red_threshold   = (46, 78, 37, 86, -29, 68)
#red_threshold   = (30, 40, 50, 60, 20, 50)
#red_thresholda   = (20, 45, 35, 45, 2 ,40)
#red_thresholdd   = (20, 45, 40, 60, 2 ,40)
#red_thresholdc   = (24, 30, 25, 42, 16 ,28)
red_threshold  =(23, 35, 40, 60, 17, 40)         #色域调整
length = []
i=0
my_length=0
err_time = 0
stop=0
my_roi = [1,30,320,41]
K=5000#the value should be measured
#############################################

while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot().lens_corr(1.8) # Take a picture and return the image.
    blobs = img.find_blobs([red_threshold],roi=my_roi)
    pin1.low()
    if len(blobs) == 1:   #扫到目标
        err_time = 0;
        b = blobs[0]
        img.draw_rectangle(b[0:4])            # rect
        img.draw_cross(b[5], b[6])            # cx, cy


        if(b[5]>175):                         #未使用pid 对目标在不在中心进行判断 效果还不错
            output_x="(r,%d\"" % (b[5]-160)
            uart.write(output_x)              #告诉单片机在那个方向

        elif(b[5]<165):
            output_x="(l,%d\"" % (160-b[5])
            uart.write(output_x)

        else :
            output_x="(s,0\""                 #已对准 ，停止找目标靶
            uart.write(output_x)
            pin1.high()
            led.on()
            time.sleep_ms(10)
            led.off()
            stop=1

        if  (stop==1):                         #测距发信号 开炮
            print('ss"')
            if((find_length(b)!=None) and (find_length(b)<330) and (find_length(b)>200)):
                length.append(find_length(b))
            if(len(length)==15):
                length.sort()
                print(length)
                for i in range(6,8):
                   my_length += length[i]
                my_length = my_length/2
                output_x="(d,%d\"" % (my_length)
                length=[]
                my_length=0
                stop=0
            print(output_x)
            uart.write(output_x)
    else:                                                  #长时间未找到目标 不在该侧的信息
        err_time += 1
        if (err_time > 10):
            print('(n,1\"')
            uart.write('(n,1\"')
            err_time = 0

    time.sleep_ms(10)


#pan_pid = PID(p=0.1, i=0, imax=90)#在线调试使用这个PID
#tilt_pid = PID(p=0.1, i=0, imax=90)#在线调试使用这个PID




    #print(clock.fps()) # Note: Your OpenMV Cam runs about half as fast while
    # connected to your computer. The FPS should increase once disconnected.

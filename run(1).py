import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
from pynput import keyboard
import numpy as np
import threading

end_flag = False

ser = serial.Serial("COM5", 9600)
if(ser.is_open):
    ser.close()
ser.open()
ser.flush()

def on_press(key):
    pass
def on_release(key):
    global ser, end_flag
    if key == keyboard.Key.esc:
        # 释放了esc 键，停止监听
        ser.close()
        end_flag = True
        return False
    

listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

recv_cnt = 0
update_flag = False
update_flag2 = False
x = 0
y = 0
ang = 0
xline = 0
yline = 0
x_array = [0]
y_array = [0]
x_line_array = [0]
y_line_array = [0]
#average = np.load('average.npy')
#average /= np.max(average)
def recv():
    global end_flag, ser, data, recv_cnt, value, update_flag, x, y, ang, x_array, y_array, update_flag2, xline, yline
    global average
    ser.flush()
    while(not end_flag):
        while(ser.read(1) != b'\xfe'):
            pass
        if(ser.read(1) == b'\xfe'):
            data = ser.read(128 * 2 + 2)
        
            if(len(data) == 128 * 2 + 2):
                if(data[-2] == 255 and data[-1] == 255):
                    value = np.frombuffer(data[0:-2], dtype="<h")
                    value.astype(np.float32)
                    #value = value / average
                    recv_cnt = recv_cnt + 1
                    update_flag = True
                    #print(len(data))
            
            data = ser.read(5 * 4 + 2)
            if(len(data) == 5 * 4 + 2):
                if(data[-2] == 255 and data[-1] == 255):
                    temp = np.frombuffer(data[4:-2], dtype=np.float32)
                    intensity = np.frombuffer(data[:4], dtype=np.int32)
                    v = temp[0]
                    ang2 = temp[1]
                    # ang = temp[2]
                    xline = temp[2]
                    yline = temp[3]
                    print(f"{intensity[0]},{v};")
                    # print(f"{ang2}")
                    if(np.abs(x - x_array[-1]) + np.abs(y - y_array[-1]) > 0.002):
                        update_flag2 = True
                        x_array.append(x)
                        y_array.append(y)
                    if(np.abs(xline - x_line_array[-1]) + np.abs(yline - y_line_array[-1]) > 0.002):
                        update_flag2 = True
                        x_line_array.append(xline)
                        y_line_array.append(yline)

            ser.flush()

            
                
recv_thread = threading.Thread(target=recv)
recv_thread.start()        

 
while(recv_cnt == 0):
    pass

# 初始化画布和图表
fig = plt.figure()
ax = plt.subplot(2,2,1)
ax2 = plt.subplot(2,2,2)
ax.set_ylim(0,3000)
line, = ax.plot(value)  
# ax2.scatter(x,y,s=1) 
line2,= ax2.plot(x_array, y_array)
track,= ax2.plot(x_line_array, y_line_array)
canvas_size = 1.5
ax2.axis("equal")
ax2.set_xlim(-canvas_size,canvas_size)
ax2.set_ylim(-canvas_size,canvas_size)

phase = 0
#FuncAnimation动画回调函数  
def update(i):       
    global update_flag, x, y, ang    
    # 更新图表数据
    if(update_flag):
        line.set_ydata(value)
        update_flag = False  
        #ax2.scatter(x,y,s=1)
        line2.set_xdata(x_array)
        line2.set_ydata(y_array) 
        track.set_xdata(x_line_array)
        track.set_ydata(y_line_array) 
        
        # 重绘图表
        # t.seth(ang)
        # scale = 10
        # t.setx(scale  * np.cos(phase))
        # t.sety(scale  * np.sin(phase))
        # phase = phase + 2 * np.pi / 1000 * 20
        
        fig.canvas.draw()  
 
# 启动定时器
ani = animation.FuncAnimation(fig, update, interval=20)  
fig.tight_layout()
plt.show()

end_flag = True

#ser.close()



 
# # 读取Excel初始数据
# data = ser.readline()
# x = df['Time']  
# y = df['Value']
 
# # 绘制初始图表(只有x、y轴)
# line, = ax.plot(x, y)   
 
# #FuncAnimation动画回调函数  
# def update(i):     
#     # 每分钟读取新数据
#     df = pd.read_excel('data.xlsx')
#     x = df['Time']  
#     y = df['Value']  
    
#     # 更新图表数据
#     line.set_xdata(x)  
#     line.set_ydata(y)   
    
#     # 重绘图表
#     fig.canvas.draw()  
 
# # 启动定时器
# ani = animation.FuncAnimation(fig, update, interval=1000)  
# plt.show()
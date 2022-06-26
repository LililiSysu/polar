import matplotlib.pyplot as plt

#1 基础绘图
#第1步：定义x和y坐标轴上的点   x坐标轴上点的数值

SNR = [ 1.000000, 1.250000, 1.500000, 1.750000, 2.000000, 2.250000, 2.500000 ]

#y坐标轴上点的数值

fast_SC_error_rate = [ 2.504785e-01, 1.520801e-01, 1.011426e-01, 5.893945e-02, 3.026855e-02, 1.407295e-02, 6.192773e-03 ]
fast_SCL2_error_rate = [ 1.619141e-01, 8.682617e-02, 4.511719e-02, 2.106348e-02, 9.720703e-03, 3.479785e-03, 1.352930e-03 ]
fast_SCL4_error_rate = [ 1.182910e-01, 5.659180e-02, 1.933594e-02, 1.060254e-02, 3.480469e-03, 1.235156e-03, 3.505859e-04 ]
fast_SCL8_error_rate = [ 9.067383e-02, 3.971680e-02, 1.481445e-02, 5.593750e-03, 1.193359e-03, 5.380859e-04, 1.291992e-04 ]
fast_SCL16_error_rate = [ 8.062500e-02, 3.253906e-02, 1.014648e-02, 3.503906e-03, 3.710938e-04, 2.805664e-04, 5.322266e-05 ]
fast_SCL32_error_rate = [ 6.900391e-02, 3.122070e-02, 6.435547e-03, 2.243164e-03, 2.597656e-04, 1.526367e-04, 1.943359e-05 ]

#第2步：使用plot绘制线条第1个参数是x的坐标值，第2个参数是y的坐标值
#plt.plot(x,y)

#2 定义绘图属性
'''
color：线条颜色，值r表示红色（red）
marker：点的形状，值o表示点为圆圈标记（circle marker）
linestyle：线条的形状，值dashed表示用虚线连接各点
'''
#plt.plot(x, y, color='r',marker='o',linestyle='dashed')
#plt.plot(x, y, 'ro')

p1,=plt.plot(SNR,fast_SC_error_rate,marker='o')
p2,=plt.plot(SNR,fast_SCL2_error_rate,marker='o')
p3,=plt.plot(SNR,fast_SCL4_error_rate,marker='o')
p4,=plt.plot(SNR,fast_SCL8_error_rate,marker='o')
p5,=plt.plot(SNR,fast_SCL16_error_rate,marker='o')
p6,=plt.plot(SNR,fast_SCL32_error_rate,marker='o')

'''
axis：坐标轴范围
语法为axis[xmin, xmax, ymin, ymax]，
也就是axis[x轴最小值, x轴最大值, y轴最小值, y轴最大值]
'''
#plt.axis([0, 6, 0, 20])


#对数坐标
#plt.xscale("log",base=2)
plt.yscale("log")

#网格
plt.grid()

#设置y轴刻度
plt.xticks(SNR)

#3 给图片添加注释和标题等

#第2步：使用plot绘制线条 第1个参数是x的坐标值，第2个参数是y的坐标值
#plt.plot(x,y)
#添加文本 #x轴文本
plt.xlabel('SNR(dB)')
#y轴文本
plt.ylabel('BER')
#标题
plt.title('error rate verse SNR, N=128, rate=0.500000')
#添加注释 参数名xy：箭头注释中箭头所在位置，参数名xytext：注释文本所在位置，
#arrowprops在xy和xytext之间绘制箭头, shrink表示注释点与注释文本之间的图标距离

#plt.annotate('I\'m annotation', xy=(2,5), xytext=(2, 10),
#            arrowprops=dict(facecolor='black', shrink=0.01),
#            )

l1 = plt.legend([p1,p2,p3,p4,p5,p6], \
                ["fast_SC_error_rate", "SCL2_decode", "SCL4_decode", "SCL8_decode", "SCL16_decode", "SCL32_decode"], \
                loc='upper right')
#添加图例

#第3步：显示图形
plt.show()

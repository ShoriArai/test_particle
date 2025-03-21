#変動する電場と一定の磁場のもとで、
#相対論的な速度を持つ電気を帯びた粒子の運動を数値的に解きつつ、
#結果をグラフで出力するプログラム
import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt
plt.rcParams["mathtext.fontset"] = "cm"

def E_field(x,y):
    return -E0*np.sin(2*np.pi*k*x)  # 電場の式（正弦波）

def equation(t, y):
    x, y_pos, px, py = y  # 位置と運動量
    
    # 速度を運動量から求める
    p_vec = np.array([px, py])
    p_norm = np.linalg.norm(p_vec)
    gamma = np.sqrt(1 + (p_norm / (m * c))**2)  # γ = sqrt(1 + (p/mc)^2)
    v_vec = p_vec / (gamma * m)
    
    # ローレンツ力
    #dpdt = q * (E + np.cross(v_vec, B))
    E_dynamic = E_field(x, y_pos)
    qbmc = q*B/(m*c)
    
    return v_vec[0], v_vec[1], qbmc * (E_dynamic + v_vec[1]), -qbmc * (v_vec[0] + beta)

#よく変更するパラメータ
t0 = 600        #時間
gamma0 = 40     #ローレンツ因子
E0 = 0.15  # 電場の振幅
k = 1/600  # 空間変化の係数
sigma = 16.834    #磁場の強さを決める値
gname = "test_particle.png" #保存する画像の名前
gformat = "png"             #ファイル形式
gdpi = 300                  #画像のdpi

#基本的に固定のパラメータ
delx = 1
m = 1           #質量
c = 1           #光速
q = -0.00446    #電荷
beta = np.sqrt((gamma0**2-1))/gamma0
v0 = -c*beta    #初速度
N1 = 100    #粒子数
B  = np.sqrt(4*np.pi*m*gamma0*sigma*N1/delx) * c    #磁場
time = np.linspace(0,t0,6000)   #時間

#数値計算、グラフ作成
result = solve_ivp(equation,(time[0],time[-1]),(600.0,0.0,v0,0.0),t_eval=time)
X = result.y[0,:]   #x座標
Y = result.y[1,:]   #y座標
Vx = result.y[2,:]  #x方向の速度
Vy = result.y[3,:]  #y方向の速度
#r = result.y[0:2,:]
#v = result.y[2:,:]
plt.plot(X,Vx,'-')
plt.xlabel("$x$",fontsize=18)
plt.ylabel("$v_x$",fontsize=18)
plt.savefig(gname,format=gformat,dpi=gdpi)
#plt.axis('scaled')
#plt.show()

#include <stdio.h>

int main(void){
    float R, ro, S, m, k, a, b, c, g;
    float x, y, Vx, Vy, t, dt, tmax;
    float k0[4], k1[4], k2[4], k3[4];
    float x1, y1, Vx1, Vy1, x2, y2, Vx2, Vy2, x3, y3, Vx3, Vy3;
    FILE* fp;

    R = 1.1;        //翼の下面と上面を横切る速度の比
    m = 70.0;       //飛ぶ人の質量
    a = 0.001;      //空気抵抗の比例係数
    b = 0.003;      //空気抵抗の比例係数
    x = 0.0;        //初期のx座標
    y = 10.0;       //初期のy座標
    Vy = 0.0;       //y方向の初速度
    tmax = 60.0;    //時間の最大値（無限ループを防ぐ）
    dt = 0.01;      //時間のきざみ幅
    char fname[] = "fly_data.txt";
    

    //Vx：x方向の初速度, S：ウイングスーツの面積, ro：大気の密度, g：重力加速度
    //例1：Vx = 11.85, S = 1.4, ro = 1.225, g = 9.8
    //例2：Vx = 10.00, S = 2.0, ro = 5.5, g = 1.4
    //例3：Vx = 65.00, S = 1.4, ro = 1.225, g = 9.8
    scanf("%f %f %f %f", &Vx, &S, &ro, &g);

    k = S * ro * (R * R - 1.0) / 2.0 / m;

    fp = fopen(fname, "w");
    fprintf(fp, "%8.4f %8.4f %8.4f %8.4f %8.4f\n", 0, x, y, Vx, Vy);
    //ルンゲクッタ法を用いた数値計算
    for(t = 0;t < tmax;t += dt){
        if (Vy > 0)   c = -1 * b;
        else    c = b;

        k0[0] = dt * Vx;
        k0[1] = dt * Vy;
        k0[2] = dt * (-a * Vx * Vx);
        k0[3] = dt * (c * Vy * Vy + k * Vx * Vx - g);
        x1 = x + k0[0] / 2.0;
        y1 = y + k0[1] / 2.0;
        Vx1 = Vx + k0[2] / 2.0;
        Vy1 = Vy + k0[3] / 2.0;
        k1[0] = dt * Vx1;
        k1[1] = dt * Vy1;
        k1[2] = dt * (-a * Vx1 * Vx1);
        k1[3] = dt * (c * Vy1 * Vy1 + k * Vx1 * Vx1 - g);

        x2 = x + k1[0] / 2.0;
        y2 = y + k1[1] / 2.0;
        Vx2 = Vx + k1[2] / 2.0;
        Vy2 = Vy + k1[3] / 2.0;
        k2[0] = dt * Vx2;
        k2[1] = dt * Vy2;
        k2[2] = dt * (-a * Vx2 * Vx2);
        k2[3] = dt * (c * Vy2 * Vy2 + k * Vx2 * Vx2 - g);

        x3 = x + k2[0];
        y3 = y + k2[1];
        Vx3 = Vx + k2[2];
        Vy3 = Vy + k2[3];
        k3[0] = dt * Vx3;
        k3[1] = dt * Vy3;
        k3[2] = dt * (-a * Vx3 * Vx3);
        k3[3] = dt * (c * Vy3 * Vy3 + k * Vx3 * Vx3 - g);

        x = x + (k0[0] + 2.0 * k1[0] + 2.0 * k2[0] + k3[0]) / 6.0;
        y = y + (k0[1] + 2.0 * k1[1] + 2.0 * k2[1] + k3[1]) / 6.0;
        Vx = Vx + (k0[2] + 2.0 * k1[2] + 2.0 * k2[2] + k3[2]) / 6.0;
        Vy = Vy + (k0[3] + 2.0 * k1[3] + 2.0 * k2[3] + k3[3]) / 6.0;
        //printf("%8.4f %8.4f %8.4f %8.4f %8.4f\n",t+dt,x,y,Vx,Vy);
        fprintf(fp, "%8.4f %8.4f %8.4f %8.4f %8.4f\n", t + dt, x, y, Vx, Vy);
        if (y < 0) break;
    }

    fclose(fp);

    return 0;
}
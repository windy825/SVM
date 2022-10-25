# :camera: Camera Calibration

카메라로 사진을 찍을 경우 현실세계의 3차원 공간이

카메라의 2차원 평면 이미지로 투영된다.

카메라에 사용된 렌즈, 렌즈와 이미지 센서와의 거리, 렌즈와 이미지 센서가 이루는 각 등 

카메라 내부 기구적인 부분에 의해서 투영된 이미지는 영향을 받게 된다.

<br>

![995410365E9F957133](https://user-images.githubusercontent.com/89068148/197343541-35beab07-855f-48fa-abe1-31f9f2ff8b7b.png)

3차원 공간이 영상에 투영된 위치를 구하거나 역으로 

영상 좌표로 부터 3차원 공간 좌표를 복원할 때는 카메라 내부 요인을 제거해야 한다.

카메라 내부 요인을 수식적인 변환 과정을 통해서 카메라의 왜곡을 보정하는 작업을

카메라 캘리브레이션이라고 한다.

다시말하면

**위와 같은 3D 공간좌표와 2D 영상좌표 사이의 변환관계 또는**

**이 변환관계를 설명하는 파라미터를 찾는 과정**이다.

<br>

<br>

## 0. Camera Calibration 개요

**[핀홀 카메라 기준]**
$$
S\begin{bmatrix} x\\y\\1 \end{bmatrix}
=
\begin{bmatrix}
f_x & skew_cf_x & c_x \\ 
0 & f_y & c_y \\ 
0 & 0 & 1
\end{bmatrix}

\begin{bmatrix}
r_11 & r_12 & r_13 & t_1 \\
r_21 & r_22 & r_23 & t_2 \\
r_22 & r_23 & r_33 & t_3 \\
\end{bmatrix}

\begin{bmatrix}
X \\
Y \\
Z \\
1 \\
\end{bmatrix}
$$

$$
S\begin{bmatrix} x\\y\\1 \end{bmatrix}
=
A

[R|t]

\begin{bmatrix}
X \\
Y \\
Z \\
1 \\
\end{bmatrix}
$$

**(X,Y,Z) :** world coordinate system 상의 3D 점의 좌표

**A :** intrinsic camera matrix

**[R|t] :** 월드 좌표계를 카메라 좌표계로 변환시키기 위한 회전/이동변환 행렬

<br>

<br>

## 1. CAMERA Calibration 획득

카메라의 파라미터를 추정하는 과정

실세계의 3D 점과 캘리브레이션된 카메라로 캡처한 이미지의 해당 2D 투영 (픽셀들) 간의 

정확한 관계를 결정하는데 필요한 **카메라에 대한 파라미터와 계수** 로 

일반적으로 아래의 두 종류의 파라미터를 복구한다. 

<br>

#### 1) Internal(intrinsic) parameters

- **Focal length 초점 거리 ** : 렌즈중심과 이미지센서(CCD, CMOS 등)와의 거리

  ![image](https://user-images.githubusercontent.com/89068148/197344984-6d6f0336-bb69-4aff-88e0-b8235aa199ee.png)

  - **f의 단위는 픽셀이다**

    특히, 이미지의 픽셀은 이미지 센서의 cell 에 대응되기 때문에, 

    초점거리는 이미지 센서의 크기에 대한 상대적인 값으로 표현된다.

    컴퓨터 비전 분야에서 의미하는 바는, 영상에서의 기하학적 해석을 용이하게 해준다.

  - **그럼 왜 fx fy로 구분하는걸까?**

    바로 이미지 센서의 cell 이 가지는 물리적인 간격 (가로길이, 세로길이) 가 

    다를 수 있음을 모델링 하기 위해서 이다.

    fx 는 이미지 셀의 x축 길이에 배수, fy는 이미지 셀의 y축 길이에 배수

    를 가진다.

  - **해상도에 따른 변화** 

    이미지 해상도를 1/2로 낮추면 캘리브레이션 결과의 초점거리도 1/2로 작아진다. 

    실제 물리적인 초점거리가 변하는 것은 아니다. 

    카메라 모델에서의 초점거리는 상대적인 개념이기 때문에 해상도를 바꾸면 

    한 픽셀(pixel)에 대응하는 물리크기가 변하기 떄문에 초점거리도 변하게 된다. 

    ex) 이미지 해상도를 1/2로 낮추면 이미지 센서의 2 x 2 cell들이 합쳐서 

    하나의 이미지 픽셀이 되기 때문에 한 픽셀에 대응하는 물리크기가 2배가 된다. 

    따라서 초점거리는 1/2이다.

<br>

- **Optical center** 광학 중심
- **Radial distortion coefficients of the lens** 렌즈의 방사 왜곡 계수

<br>

#### 2) External(extrinsic) parameters

​      카메라 설치 높이, 방향 (팬, 틸트) 등 카메라와 외부 공간과의 기하학적 관계에

​      관련된 파라미터

- **Rotation and translation** 월드 좌표계에 대한 카메라의 방향 (회전 및 이동)



#### 활용한 예시

geometric calibration을 사용하여 추정된 렌즈의 파라미터를 이용하여 왜곡 제거 예시

![image](https://user-images.githubusercontent.com/89068148/195746045-77fb5b5c-ae9e-49e1-9662-1076fe91381e.png)




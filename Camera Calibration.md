# :camera: Camera Calibration

카메라로 사진을 찍을 경우 현실세계의 3차원 공간이

카메라의 2차원 평면 이미지로 투영된다.

카메라에 사용된 렌즈, 렌즈와 이미지 센서와의 거리, 렌즈와 이미지 센서가 이루는 각 등 

카메라 내부 기구적인 부분에 의해서 투영된 이미지는 영향을 받게 된다.

<br>

3차원 공간이 영상에 투영된 위치를 구하거나 역으로 

영상 좌표로 부터 3차원 공간 좌표를 복원할 때는 카메라 내부 요인을 제거해야 한다.

**카메라 내부 요인을 수식적인 변환 과정을 통해서 카메라의 왜곡을 보정하는 작업을 **

**카메라 캘리브레이션**이라고 한다.

<br>



<br>

### 1. CAMERA Calibration 획득

카메라의 파라미터를 추정하는 과정

실세계의 3D 점과 캘리브레이션된 카메라로 캡처한 이미지의 해당 2D 투영 (픽셀들) 간의 

정확한 관계를 결정하는데 필요한 **카메라에 대한 파라미터와 계수** 로 

일반적으로 아래의 두 종류의 파라미터를 복구한다. 

<br>

#### 1) Internal(intrinsic) parameters

- **Focal length** 초점 거리 
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




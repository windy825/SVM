## Fish-eye lens , 버드아이뷰

<br>

### 1. CAMERA Calibration 획득

카메라의 파라미터를 추정하는 과정 입니다.

실세계의 3D 점과 캘리브레이션된 카메라로 캡처한 이미지의 해당 2D 투영 (픽셀들) 간의 정확한 관계를 결정하는데 필요한 **카메라에 대한 파라미터와 계수** 로 일반적으로 아래의 두 종류의 파라미터를 복구 합니다. 

<br>

#### 1) Internal parameters

- **Focal length** 초점 거리 
- **Optical center** 광학 중심
- **Radial distortion coefficients of the lens** 렌즈의 방사 왜곡 계수

<br>

#### 2) External parameters

- **Rotation and translation** 월드 좌표계에 대한 카메라의 방향 (회전 및 이동)



#### 3) 활용한 예시

geometric calibration을 사용하여 추정된 렌즈의 파라미터를 이용하여 왜곡 제거 예시

![image](https://user-images.githubusercontent.com/89068148/195746045-77fb5b5c-ae9e-49e1-9662-1076fe91381e.png)




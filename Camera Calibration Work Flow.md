#### **1단계: 체커보드 패턴으로 실세계 좌표 정의**



![img](https://blog.kakaocdn.net/dn/OvzOB/btrdyjGf9Kl/nkY1VNLKKNQ9GS1YARPpv0/img.jpg)



**세계 좌표계(World Coordinate System):** 우리의 세계 좌표는 방의 벽에 부착된 이 체커보드 패턴으로 고정됩니다. 3D점은 체커보드에 있는 사각형의 코너입니다. 위 보드의 모든 코너는 세계 좌표계의 원점으로 선택할 수 있습니다. X_w와 Y_w 축은 벽을 따라 있으며, Z_w축은 벽에 수직입니다. 따라서 체커보드의 모든 점은 XY 평면에 있습니다(즉, Z_w = 0 ).

 

캘리브레이션 과정에서, 우리는 알고 있는 3D 점(X_w, Y_w, Z_w)과 해당 픽셀 위치 (u, v) 이미지 세트로 카메라 파라미터를 계산합니다.

 

3D 점의 경우 다양한 방향에서 알려진 차원의 체커보드 패턴을 촬영합니다. 세계 좌표는 체커보드에 붙어있고 모든 꼭짓점이 평면 위에 있기 때문에, 우리는 모든 점이 0이 되도록 Z_w를 임의로 선택할 수 있습니다. 점들은 체커보드에서 균등하게 간격을 두고 있기 때문에, 각 3D 점의 (X_w, Y_w) 좌표는 한 점을 기준점(0, 0), 그 기준점을 기준으로 나머지를 정의함으로써 쉽게 정의할 수 있습니다.

------

#### **캘리브레이션에서 체커보드 패턴이 널리 사용되는 이유는 무엇입니까?**

체커보드 패턴은 이미지에서 뚜렷하고 쉽게 감지할 수 있습니다. 뿐만 아니라, 체커보드의 사각형 코너는 두 방향으로 급격한 기울기를 가지므로 위치 파악에 이상적입니다. 또한, 이러한 코너는 체커보드 선의 교차점에 있다는 사실과도 관련이 있습니다. 이러한 모든 사실은 체커보드 패턴에서 사각형의 코너를 견고하게 찾는데 사용됩니다.



![img](https://blog.kakaocdn.net/dn/b3Wmg6/btrduT87uE1/pzsWbdTUB7XBHv8zhFogmk/img.jpg)



감지된 체커보드 코너를 그린 후 결과

------

#### **2단계: 다양한 시점에서 체커보드의 여러 이미지 캡처**



![img](https://blog.kakaocdn.net/dn/Eis6t/btrdyljINax/vnZHz2DkBmxKUjArzBsqMK/img.gif)



 

다음으로, 체커보드를 정적으로 유지하고 카메라를 움직여 체커보드의 여러 이미지를 찍습니다. 또는 카메라를 일정하게 유지하고 다른 방향에서 체커보드 패턴을 촬영할 수도 있습니다. 두 상황은 수학적으로 유사합니다.



![img](https://blog.kakaocdn.net/dn/mr3ua/btrdISPqjTo/pWlkTrgRMI4WxCpvcD54pk/img.png)



------

#### **3단계 : 체커보드의 2D 좌표 찾기**


이제 체커보드 이미지가 여러 장 있습니다. 우리는 또한 세계 좌표에서 체커보드에 있는 점의 3D 위치를 알고 있습니다. 마지막으로 필요한 것은 이미지에서 이러한 체커보드 코너의 2D 픽셀 위치입니다.

------

#### **3.1 체커보드 코너 찾기** 

OpenCV는 체커보드를 찾고 코너 좌표를 반환하는 findChessboardCorners라는 내장 함수를 제공합니다.

```python
retval, corners = cv2.findChessboardCorners(image, patternSize, flags)
```

 

| **image**       | 소스 체커보드 사진. 8-bit 그레이스케일 또는 컬러 이미지 |
| --------------- | ------------------------------------------------------- |
| **patternSize** | 체커보드 행과 열당 내부 코너 수                         |
| **corners**     | 감지된 코너의 출력 배열                                 |
| **flags**       | 다양한 작업 플래그                                      |

패턴이 감지되었는지 여부에 따라 출력은 true 또는 false입니다.

------

#### **3.2 체커보드 코너 개선**


좋은 캘리브레이션은 정밀도(precision)에 관한 것입니다. 좋은 결과를 얻으려면 서브픽셀(sub-pixel) 수준의 정확도로 코너 위치를 얻는 것이 중요합니다.

OpenCV의 함수 cornerSubPix는 원본 이미지와 코너 위치를 가져와서 원래 위치의 작은 이웃 내에서 가장 좋은 코너 위치를 찾습니다. 알고리즘은 완전히 반복적이므로 종료 기준(예: 반복 횟수 및/또는 정확도)을 지정해야 합니다.

```
cv2.cornerSubPix(image, corners, winSize, zeroZone, criteria)
```

| **image**    | 입력 이미지                                                  |
| ------------ | ------------------------------------------------------------ |
| **corners**  | 입력 코너의 초기 좌표와 출력을 위해 제공되는 개선 좌표       |
| **winSize**  | 검색 창의 측면 길이의 절반                                   |
| **zeroZone** | 아래 공식의 합산이 이루어지지 않은 탐색 영역 중앙에 있는 사각 영역(dead region) 크기의 절반. 자기상관 행렬(autocorrelation matrix)의 가능한 특이성을 피하기 위해 때때로 사용. (-1,-1) 값은 그러한 크기가 없음을 나타냄. |
| **criteria** | 코너 미세 조정(corner refinement)의 반복 프로세스 종료 기준. 즉, 코너 위치 미세 조정 프로세스는 criteria.maxCount 반복 후 또는 일부 반복에서 코너 위치가 criteria.epsilon보다 작게 이동할 때 중지됨. |

 

------

#### **4단계: 카메라 캘리브레이션**


캘리브레이션의 마지막 단계는 세계 좌표의 3D 점과 모든 이미지의 2D 위치를 OpenCV의 calibrateCamera방법으로 전달하는 것입니다. 구현은 Zhengyou Zhang의 [논문](https://www.microsoft.com/en-us/research/wp-content/uploads/2016/02/tr98-71.pdf)을 기반으로 합니다.

calibrateCamera에 대한 구문을 살펴보겠습니다.

```
retval, cameraMatrix, distCoeffs, rvecs, tvecs = cv2.calibrateCamera(objectPoints, imagePoints, imageSize)
```

| **objectPoints** | 3D 점 벡터로 구성된 벡터. 외부 벡터는 패턴 사진의 수만큼 요소를 포함 |
| ---------------- | ------------------------------------------------------------ |
| **imagePoints**  | 2D 이미지 점 벡터로 구성된 벡터                              |
| **imageSize**    | 이미지의 크기                                                |
| **cameraMatrix** | 내부 카메라 행렬                                             |
| **distCoeffs**   | 렌즈 왜곡 계수(Lens distortion coefficients)                 |
| **rvecs**        | 회전은 3×1 벡터로 지정. 벡터의 방향은 회전 축을 지정하고 벡터의 크기는 회전 각을 지정 |
| **tvecs**        | 3×1 이동 벡터                                                |

------

#### **카메라 캘리브레이션 코드**

```python
import cv2
import numpy as np
import os
import glob
# 체커보드의 차원 정의
CHECKERBOARD = (6,9) # 체커보드 행과 열당 내부 코너 수
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
# 각 체커보드 이미지에 대한 3D 점 벡터를 저장할 벡터 생성
objpoints = []
# 각 체커보드 이미지에 대한 2D 점 벡터를 저장할 벡터 생성
imgpoints = [] 
# 3D 점의 세계 좌표 정의
objp = np.zeros((1, CHECKERBOARD[0] * CHECKERBOARD[1], 3), np.float32)
objp[0,:,:2] = np.mgrid[0:CHECKERBOARD[0], 0:CHECKERBOARD[1]].T.reshape(-1, 2)
prev_img_shape = None
# 주어진 디렉터리에 저장된 개별 이미지의 경로 추출
images = glob.glob('./images/*.jpg')
for fname in images:
    img = cv2.imread(fname)
    # 그레이 스케일로 변환
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    # 체커보드 코너 찾기
    # 이미지에서 원하는 개수의 코너가 발견되면 ret = true
    ret, corners = cv2.findChessboardCorners(gray,
                                             CHECKERBOARD,
                                             cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_FAST_CHECK + cv2.CALIB_CB_NORMALIZE_IMAGE)
    # 원하는 개수의 코너가 감지되면,
    # 픽셀 좌표 미세조정 -> 체커보드 이미지 표시
    if ret == True:
        objpoints.append(objp)
        # 주어진 2D 점에 대한 픽셀 좌표 미세조정
        corners2 = cv2.cornerSubPix(gray, corners, (11,11),(-1,-1), criteria)
        imgpoints.append(corners2)
        # 코너 그리기 및 표시
        img = cv2.drawChessboardCorners(img, CHECKERBOARD, corners2, ret)
    cv2.imshow('img',img)
    cv2.waitKey(0)
cv2.destroyAllWindows()
h,w = img.shape[:2] # 480, 640
# 알려진 3D 점(objpoints) 값과 감지된 코너의 해당 픽셀 좌표(imgpoints) 전달, 카메라 캘리브레이션 수행
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
print("Camera matrix : \n") # 내부 카메라 행렬
print(mtx)
Camera matrix : 
[[469.18043387   0.         259.40407955]
 [  0.         454.89333646 218.33055988]
 [  0.           0.           1.        ]]
print("dist : \n") # 렌즈 왜곡 계수(Lens distortion coefficients)
print(dist)
dist : 
[[ 0.15034446 -0.03940961 -0.0046684  -0.01587236 -0.1004698 ]]
print("rvecs : \n") # 회전 벡터
print(rvecs)
rvecs : 
[array([[-0.21876227],
       [-0.04970272],
       [ 1.53439193]])]
print("tvecs : \n") # 이동 벡터
print(tvecs)
tvecs : 
[array([[ 7.11219416],
       [-2.02346387],
       [12.79357913]])]
```
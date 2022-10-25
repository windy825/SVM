# 영상 Geometry 

<br>

#### **3D 월드 좌표계, 3D 카메라 좌표계, 2D 정규 좌표계, 2D 영상(픽셀) 좌표계**

영상 geometry에서는 크게 4가지 좌표계가 존재한다.

여기서 SVM 프로젝트에 관련해서 주로 사용할 좌표계는 월드, 카메라, 픽셀 이다.

<br>

![image](https://user-images.githubusercontent.com/89068148/196459714-2b97c63a-183f-4b72-9fa5-039d21492013.png)

<br>

#### [1] 3D World Coordinate System

현실세계에서 물체의 위치를 표현할때 사용하는 좌표계이다.

기준 원점은 임의로 설정할 수 있다. 

그러나 좌표계는 일종의 약속 이기 때문에 이 월드 좌표계 안에서 만큼은 

(X, Y, Z) 라고 정의한 점에 대해서 위치가 어디인지 유일하게 결정될 수 있어야 한다.

<br>

#### [2] 3D Camera Coordinate System

![image](https://user-images.githubusercontent.com/89068148/196462590-614252fd-33e9-4a0d-a7b2-d6e95c60f514.png)

월드 좌표계와 동일하나, 기준 원점만 카메라를 기준으로 한다.

특히, 초점(카메라 렌즈의 중심)을 기준 원점으로 하며, 카메라 기준 3D 좌표계의 

3축 방향은 위 사진과 같다.

월드 좌표계에서 카메라 위치는 월드 좌표계의 3축을 기준으로 각각 얼마나 이동했는지를 통해, 

좌표를 알 수 있다.

카메라가 월드 좌표계에서 바라보는 방향은 카메라의 R (회전 파라미터)를 통해 파악한다. 

<br>

#### [3] 2D Pixel Image Coordinate System

`픽셀 좌표계 or 영상 좌표계`

위 사진에서 픽셀 좌표계의 x,y 축에 의해 결정되는 평면을 `image plane` 이라고 함

기하학적으로 볼 때, 3D 월드 공간상의 한 점 P = (X,Y,Z)는 렌즈의 초점을 지나서 

이미지 평면의 한 점 pimg = (x, y)에 투영(projection) 된다.

점 P와 점 pimg를 잇는 선(ray) 상에 있는 모든 3D 점들은 모두 pimg로 투영되는데, 

3D 점 P로부터 pimg는 유일하게 결정할 수 있지만, 반대로 

**영상 픽셀 pimg로부터 월드의 P좌표를 구하는 것은 부가적인 정보 없이는 불가능**함

 <br>

#### [4] 2D Normalized Image Coordinate System

`intrinsic parameter`의 영향이 제거된 가상의 좌표계.

또한 좌표계의 단위를 없앤 **정규화된 좌표계**이며 카메라 초점과의 거리가 1인 

가상의 이미지 평면을 정의하는 좌표계 이다.

(이전

의 이미지 평면을 평행이동시켜, 초점과의 거리가 1인 지점으로 옮긴 이미지 평면임)

![제목 없음](https://user-images.githubusercontent.com/89068148/197330037-97ddc196-50bd-41b4-bee6-04dced6ba5c4.png)

`p' = (u,v)`을   `p img = (x,y)` 으로 좌표 변환

여기서 `f` 초점거리이고 `c`는 주점이다.
$$
\begin{bmatrix}x\\y\\1 \end{bmatrix}
=
\begin{bmatrix}
f_x & 0 & c_x \\
0 & f_y & c_y \\
0 & 0 & 1 \\
\end{bmatrix}

\begin{bmatrix}u\\v\\1 \end{bmatrix}
$$
식을 정리하면,
$$
[픽셀 좌표]\\
x = f_xu + c_x
\\
y = f_yv + c_y
\\
\\
[정규좌표]\\
u = (x-c_x)/ f_x
\\
v = (y-c_y)/f_y
$$
<br>

#### [5] 왜 정규화 좌표계가 필요한가 ?

**카메라 간의 차이는 어떤 일관된 기하학적인 해석을 하는데 있어서 불필요한 요소**이다. 

특히, 이미지가 맺히는 상과 초점 간의 거리가 카메라 마다 다를 수 있다.

따라서, 이러한 요소를 제거한 정규화된 이미지 평면에서 공통된 기하학적 특성을 분석하고 

이론을 수립하는 것이 보다 효과적일 것이다.

---

참고 : 

https://darkpgmr.tistory.com/m/77

https://intuitive-robotics.tistory.com/m/111
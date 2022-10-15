참고 : 김진솔님 블로그 https://gaussian37.github.io/vision-concept-calibration/

<br>

<br>

## :camera:  카메라의 이미지 형성 방식

<br>

#### 1. 핀홀 카메라 원리

이미지 형성의 기본 아이디어는 빛을 통한 물체 인식으로 출발한다.

특히, 물체에 맞고 반사되어 나온 광선을 포착하는 것이 아이디어임.





![image](https://user-images.githubusercontent.com/89068148/195979161-7fb2367c-a9bf-49ae-a9c5-a4f2111da782.png)

그러나, 위 그림처럼 미디엄에 맺히는 물체의 모습은 엉망으로 보일 수있다.

물체에 맞고 나온 다른 rays 광선들이 모두 겹치기 때문

![image](https://user-images.githubusercontent.com/89068148/195979237-8d10bdc6-8163-4f39-b3c5-572c1e2d3a0d.png)

따라서 위 그림처럼 핀-홀 구조로, 물체의 각 위치들이 미디엄의 픽셀 간 일대일 대응이 될 수

있도록 만든다.

그럼, 미디엄의 한 픽셀에 전 그림처럼 여러 부분이 겹치지 않는다.

![image](https://user-images.githubusercontent.com/89068148/195979348-fd8dfbf8-d688-49fc-a555-ac12b51f6679.png)

하지만 광선을 통해 미디엄에 맺히는 물체는 위치가 반전된다. 

카메라 핀홀을 통해 들어온 광선들은 직선이기 때문에, 

상하뿐만아니라, 모든 좌표가 핀홀 점과 대칭되도록 반전되는 것이다.

이 성질을 이용하여 수학적으로 모델링을 해야 한다.

<br>

#### 2. 수학적 모델링

**1) 가정**

- 


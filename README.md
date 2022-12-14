# :car: SVM 프로젝트
fish-eye 렌즈를 활용한 **TOP VIEW 및 BOWL VIEW** 개발 합니다.
렌즈 FOV : 수직 150, 수평 187
python, c++ 
openCV, openGL
<br>
<br>
<br><2022.11.03> 진행상황 공유 : 첫 정합 테스트가 실시 되었습니다.

![surround3](https://user-images.githubusercontent.com/89068148/199689801-a9e7f260-26f1-452a-a1fe-f030cae9f403.jpg)

<br>

<br>

<2022.10.28> 진행상황 공유 : calibration을 통한 왜곡 보정 및 기구설치 파트

![그림1](https://user-images.githubusercontent.com/89068148/198588073-020692a1-3c87-4a12-8439-fc6851a12aa4.png)



추후 상세 개발 내용 추가 하겠습니다.

<br>

<br>

## :question: 왜 SVM 개발을 하는가 ?

 현재 자율주행  차량 시장은 명확한 공통 기술 표준이 없는 상황으로 각 업체들마다  

미국 자동차 공학회에서 제시한 자율주행 3단계 이상의   상용화를  목표로 경쟁중 입니다.  

먼저 상용화에  성공하는 완성차 업체가 새로운 자율주행 분야의   기술 표준이  될 것이기 때문에 

저마다의 기술 표준을 내세워 자율주행 시스템을 개발중에 있습니다. 

자율주행  분야에서 자동 주행 또는 자동 주차 기능은 

항상 SVM 시스템과 연동되어 동작하는 경우가 많습니다.  

<br>

따라서 **어안렌즈를 활용한 SVM 시스템의 개선 또는 새로운 기술 발전은**   

**곧 자율주행 시장에서의 경쟁력을 확보 하는데 큰 역할을 할 것**이라고 생각합니다.

<br>

## :running: 목표 ?

카메라 영상 보정 및 합성을 통한 탑뷰를 정밀하게 구현하여 기술을 터득한뒤, 

향후 목표인 자율주행 및 자율비행 직무에 활용하겠습니다.

또한 카메라 센서를 활용한 데이터 처리의 기반 지식을 얻는데 활용합니다

<br>

### :rocket:  저장소 index

[**Computer Graphics 관련 연구**](https://github.com/windy825/SVM/tree/master/Computer%20Graphics)

- 2차원, 3차원 좌표계
- 회전행렬 + 기저변환
- Camera Calibration 
- Pin-hole Camera Calibration Basics
- 삼각함수
- fish-eye

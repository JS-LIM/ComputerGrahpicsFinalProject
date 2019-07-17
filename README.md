# ComputerGrahpicsFinalProject

## TITLE : SaveTheIronMan!


### 프로젝트 목적
 이번 프로젝트의 목적은 지금까지 강의 시간에 배운 내용을 기반으로 하여 다양하게 활용해서  3D 게임을 만드는 것이다. 그렇기 때문에 강의 시간에 배운 3D 그래픽스의 기초적인 내용의 바탕이 되는 Modeling, View Control, Animation, Particle System, Texturing 등을 잘 결합해서 3D 게임을 만드는 것이다.
### 프로젝트 설명
 Modeling, View Control, Animation, Particle System, Texturing 기법을 적절하게 활용한 3D 게임을 만들었다. 이 게임은 아이언맨이 목적지까지 안전하게 도착하게 하는 게임이며, 도착지는 텍스쳐 애니메이션이 입혀진 원형의 포탈이다. 플레이어는 게임 속 주인공인 아이언맨을 컨트롤 할 수 있다. 상하전후좌우 6방향으로 컨트롤 할 수 있으며, 마우스 우클릭 시 미사일을 발사할 수 있다. 미사일로는 우주 공간에 있는 몬스터와 다양한 색깔의 행성들을 파괴할 수 있다. 그리고 우주 공간에서 날라오는 초록색의 미사일들과 몬스터, 행성과 충돌하게 되면 게임은 끝나게 된다.

- Modeling

StaticTriangularSurface 클래스를 이용하여 다양한 obj 파일들을 띄웠다. 이 게임에서는 플레이어가 조종하는 아이언맨, 다양한 색깔의 행성들, 날아다니는 몬스터, 목적지 포탈이 모델링이 적용되었다.
- View Control

플레이어가 아이언맨을 움직이는 방향으로 카메라의 시점도 같이 움직이게 된다. 카메라의 시점 변경은 GL_VIEW에 추가적으로 SetMode 함수를 구현하여 적용했다.
- Particle System

이 게임에서 Particle System이 적용된 부분은 아이언맨이 쏘는 미사일, 우주에서 날아오는 미사일 그리고 맵에서 생성되는 원형의 고리다. (추가적으로 MissileSystem.h, Fountain.h를 구현)
- Texturing

Texturing이 적용된 부분은 원형의 목적지 포탈이다. 원형의 목적지 포탈은 obj형태의 sphere지만 readBMP를 통해서 불러온 bmp 이미지를 obj에 입혀 Texturing 효과를 구현했다.
- Animation

Texturing이 적용된 원형의 목적지 포탈에 updatePhongSurfaceWithTexture 함수를 적용시켜서 bmp 이미지가 obj물체에서 움직이는 듯한 animation 효과를 주었다.
### 동영상 링크
<https://youtu.be/isBMomBdWR0>

### 게임 화면

![image](https://user-images.githubusercontent.com/22046757/61382103-141f0600-a8e7-11e9-95b5-4d674c885ca9.png)
 
처음 게임의 시작 화면으로 화면의 가운데에 플레이어가 조종할 아이언맨이 있으며, 우주 공간에는 날아다니는 미사일과 몬스터, 고정되어 있는 행성, 그리고 아이언맨이 가야할 목적지 포탈이 있다.

![image](https://user-images.githubusercontent.com/22046757/61385420-577c7300-a8ed-11e9-917a-b93da4df3606.png)

아이언맨이 성공적으로 목적지에 도착했을 때의 결과로써 성공적으로 목적지에 도착했다는 메시지 박스가 나타난다.

![image](https://user-images.githubusercontent.com/22046757/61385432-5fd4ae00-a8ed-11e9-9dac-069445d2f216.png) 

아이언맨이 목적지에 가는 도중에 충돌했을 때 나타나는 결과로써 미션에 실패했다는 메시지 박스가 나타난다.

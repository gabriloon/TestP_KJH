# TestP_KJH

This is a game that looked at the requirements and made a test using Unreal Engine.<br>
<br>
This repository contains:<br>
	1.Contains the code of the project.<br>
	2.Background of the project.<br>
	3.Contributor.<br>
	
## 목차
- [BackGround](#BackGround)
- [Description](#Description)
- [Related Efforts](#RelatedEfforts)
- [Contributor](#Contributor)



## BackGround
It's a 3D side-scrolling game, the player can attack with the Q and W keys.<br>
If the Q key is pressed for less than 3 seconds, the basic attack will fly in front of the player.<br>
If you hold down Q for more than 3 seconds, you will launch an attack with a range 3 times wider than your basic attack.<br>
When the W key is pressed, a blue-colored attack will fly, and if the attack touches an object, it has the ability to fly to the opposite side.<br>
If the Q key is pressed for less than 1 second and the W key is pressed, the same attack as the basic attack will fly, but after 3 seconds, the attack will fly in three separate directions.<br>
The player's attack is recorded on the UI in the upper right corner, and when the Reset button is pressed, the record is reset.<br><br><br>
**For the smooth execution of this code, let's briefly introduce the sequence:**<br>
1.There are 4 types of attacking actors in c++ format. Among them, in the case of SplitArrowActor and ReflectArrow.cpp, in order to designate a Spawn Actor, you need to create a Blueprint.<br>
SplitArrowActor: Assign an ArrowActor to SpawnToActor in the Details window.<br>
ReflectArrow: Assign Self to SpawnToActor and You can put the desired Material into MaterialBlue. <br>
<br>
2.Access the player character actor and in the details window. <br>
NormalArrowActor: ArrowActor <br>
ChargeArrowActor: ChargeArrowActor <br>
SplitArrowActor: The Split Arrow Blueprint Actor created in step 1 <br>
ReverseArrowActor: The ReverseArrow Blueprint Actor created in step 1. <br>
3.In the case of UI widgets, there are components such as Text, button, and progressbar in cpp, <br>
which can be used by placing each component and performing a bind action. <br> <br>
## Description
The contents of each *folder* are as follows.<br><br>
If you want to check the **code**, it is in the path *TestP_KJH/Source/NeopleTestP_KJH*.
<br>
Attack function:
ArrowActor,ChargeArrowActor,ReflectArrow,SplitArrowActor
<br>
Character input related function: NeopleTestP_KJHCharacter
<br>
UI related features: ProjectileUserWidget.
<br>
## RelatedEfforts
Main Engine: [Unreal engine](https://www.unrealengine.com/ko/)<br>

## Contributor
gabriloon

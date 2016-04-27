/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 2.0
* 
* �ļ�����: Sim_Model.cpp
* ��ǰ�汾: V 2.0.0
* �ļ���ʶ: �����������main()����
* ��������: Ϊģ�Ϳ��������ṩ�����ڵ��֧��
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include <malloc.h>
#include <TIME.H>
#include "Sns_Scenarios.h"

static void Sns_main();

int main(int argc, char* argv[])
{
	
	Sns_main();

	return 0;
}

void Sns_main()
{
	Sns_Scenarios *ScenariosData;
	ScenariosData = new Sns_Scenarios();

	printf("SNSim Init is beginning......\n");
	ScenariosData->SNS_Init();			//���л�����ʼ��
	printf("SNSim Running is beginning......\n");
	ScenariosData->SNS_Simulate_Run();	//�����¼�������
	printf("SNSim Data record is beginning......\n");
	ScenariosData->SNS_Simulate_End();	//�����������ض�������
	printf("SNSim is end.\n");
	system("pause");
}

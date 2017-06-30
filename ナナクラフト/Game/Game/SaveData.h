#pragma once
#include <iostream>
#include <fstream>
using namespace std;


class SaveData :public IGameObject
{
public:
	SaveData();
	~SaveData();
	void LoadDatas();
	void SaveDatas();
	void Update();


	float SaveTime = 0;  //そのための,タイマー

};


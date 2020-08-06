#pragma once
#include "Service.h"
#include <cstring>
#include <iostream>
#include <vector>


class UI
{
private:
	Service<BaseRepository>& service;
	bool modeA = false;
	bool modeB = true;

	bool csv_type = false;
	bool html_type = false;

	std::string powerwordname;
	std::string material;
	int age = 0;
	std::string corporealform;
	int position = 0;

public:
	UI(Service<BaseRepository>& service): service{service} { }

	void start_program();
	void List(std::vector<TElems>);
	void ListAll();
	void Next(int);
	void SaveStatue(std::string);
	void filterAfterMaterialAndAge(std::string material, int age);
	void ListMyList();
	void ParseCommand();

	void FileLocation(char* pointerToline);
	void MylistLocation(char* pointerToline);
	void AddStatueUI(char* pointerToLine);
	void UpdateStatueUI(char* pointerToLine);
	void GetParameters(int i, char* pointerToLine);
	void DeleteStatueUI(char* pointerToLine);
	void ModeChangeUI(char* pointerToLine);
	void NextStatueUI(char* pointerToLine);
	void FilterUI(char* pointerToLine);
	void ListUI(char* pointerToLine);
	void SaveStatueUI(char* pointerToLine);
};


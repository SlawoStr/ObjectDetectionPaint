#pragma once
#include "pyhelper.h"
#include <vector>
#include <string>

class PythonConnector
{
public:
	PythonConnector();
private:
	CPyInstance hInstance;
	CPyObject pythonClass;
	CPyObject digitPredictor;
	CPyObject objectPredictor;
	bool ErrorCondition;
public:
	std::vector<float>predictImage();
	void predictObject();
};
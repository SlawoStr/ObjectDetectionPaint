#include "PythonConnector.h"
#include <iostream>

std::vector<float> listTupleToVector_Float(PyObject* incoming) {
	std::vector<float> data;
	if (PyTuple_Check(incoming)) {
		for (Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			PyObject* value = PyTuple_GetItem(incoming, i);
			data.push_back(PyFloat_AsDouble(value));
		}
	}
	else {
		if (PyList_Check(incoming)) {
			for (Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
				PyObject* value = PyList_GetItem(incoming, i);
				data.push_back(PyFloat_AsDouble(value));
			}
		}
		else {
			throw std::logic_error("Passed PyObject pointer was not a list or tuple!");
		}
	}
	return data;
}

PythonConnector::PythonConnector()
{
	// Python script name without .py
	CPyObject pName = PyUnicode_FromString("DigitRecognizer");
	// Import module
	CPyObject pModule = PyImport_Import(pName);

	CPyObject dict;

	ErrorCondition = false;
	if (pModule)
	{
		//Get dictionary object that implements module's namespace (__dict__)
		dict = PyModule_GetDict(pModule);
		if (dict == nullptr) {
			PyErr_Print();
			std::cerr << "Fails to get the dictionary.\n";
			ErrorCondition = true;
		}
		else
		{
			digitPredictor = PyObject_GetAttrString(pModule, "predictDigit");
			objectPredictor = PyObject_GetAttrString(pModule, "predictObject");
		}
	}
	else
	{
		std::cerr << "ERROR: Module not imported2\n" << std::endl;
		ErrorCondition = true;
	}
}

std::vector<float> PythonConnector::predictImage()
{
	CPyObject result = PyObject_CallFunction(digitPredictor, NULL);
	std::vector<float> vecResult = listTupleToVector_Float(result);
	return vecResult;
}

void PythonConnector::predictObject()
{
	CPyObject result = PyObject_CallFunction(objectPredictor, NULL);
}

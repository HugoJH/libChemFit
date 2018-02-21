#include "PythonInterface.h"

#include <QVariantList>
#include <iostream>
#include <QDebug>


PythonInterface& PythonInterface::getInstance()
{
   static PythonInterface PyInterface;
   return PyInterface;
}

PythonInterface::PythonInterface()
{
   Py_Initialize();
   PyRun_SimpleString ("import sys; sys.path.insert(0, '.')\n");
}

PythonInterface::~PythonInterface()
{
   Py_Finalize();
}

PyObject* PythonInterface::importModule(const QString& moduleName)
{
   PyObject* name = PyUnicode_FromString(qPrintable(moduleName));
   PyObject* module = PyImport_Import(name);
   Py_XDECREF(name);
   return module;
}

PyObject* PythonInterface::loadArguments(const QVariantList& args)
{
   PyObject* arguments = PyTuple_New(args.size());

   for (int i = 0; i < args.size(); ++i)
   {
      PyObject* object = nullptr;

      if (args[i].type() == QVariant::Double)
      {
         object = PyFloat_FromDouble(args[i].toDouble());
      }
      else if(args[i].type() == QVariant::List)
      {
         QVariantList list = args[i].toList();
         object = PyTuple_New(list.size());

         for (int j = 0; j < list.size(); ++j)
         {
            PyObject* item = PyFloat_FromDouble(list[j].toDouble());
            PyTuple_SET_ITEM(object, j, item);
         }
      }
      else
      {
         std::cout << "Unknown argument object type";
      }

      PyTuple_SET_ITEM(arguments, i, object);
   }
   return arguments;
}

PyObject* PythonInterface::prepareFunction(PyObject* module, const QString& function)
{
   return PyObject_GetAttrString(module, qPrintable(function));
}

QVariant PythonInterface::callFunction(const QString& moduleName, const QString& functionName, const QVariantList& arguments)
{
   PyObject* pyModule = importModule(moduleName);

   if (pyModule == nullptr)
   {
      std::cout << "Error loading module" <<std::endl;
      PyErr_Print();
      return QVariantList();

   }

   PyObject* pyFunction = prepareFunction(pyModule,functionName);

   if (pyFunction == nullptr)
   {
      std::cout << "Error preparing Function" <<std::endl;
      PyErr_Print();
      return QVariantList();
   }

   PyObject* PyArguments = loadArguments(arguments);
   PyObject* pyOutput = PyObject_CallObject(pyFunction, PyArguments);

   if (pyOutput == nullptr)
   {
      std::cout << "Either Wrong parameters or wrong function object";
      return QVariantList();
   }

   return prepareOutput(pyOutput);
}

QVariant PythonInterface::prepareOutput(PyObject* pyOutput)
{
   QVariant output;
   QString outputType = pyOutput->ob_type->tp_name;

   if (outputType == "list")
   {
      QVariantList list;
      int listSize = PyList_Size(pyOutput);
      for (int x = 0; x < listSize; ++x)
      {
         QVariant item = prepareOutput(PyList_GetItem(pyOutput, x));
         list.push_back(item);
      }
      output = list;
   }
   else if (outputType == "float")
   {
      output = PyFloat_AsDouble(pyOutput);
   }
   else if (outputType == "int")
   {
      output = PyLong_AsLongLong(pyOutput);
   }
   else
   {
      qDebug() << outputType << "to be implemented";
   }

   return output;
}



#ifndef PYTHONINTERFACE_H
#define PYTHONINTERFACE_H

#include <QString>
#include <Python.h>
#include <QVariantList>

class PythonInterface
{
   public:
      PythonInterface();
      ~PythonInterface();

      PyObject* importModule(const QString & moduleName);
      PyObject* loadArguments(const QVariantList& args);
      PyObject* prepareFunction(PyObject* module, const QString& function);
      QVariant callFunction(const QString& moduleName,
                                const QString& functionName,
                                const QVariantList& arguments);
      QVariant prepareOutput(PyObject* pyOutput);
};

#endif // PYTHONINTERFACE_H

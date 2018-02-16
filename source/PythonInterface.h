#ifndef PYTHONINTERFACE_H
#define PYTHONINTERFACE_H

#include <QString>
#undef slots
#include <Python.h>
#include <QVariantList>

class PythonInterface
{
   public:
      PythonInterface();
      ~PythonInterface();

      QVariant callFunction(const QString& moduleName,
                            const QString& functionName,
                            const QVariantList& arguments);
   private:
      PyObject* importModule(const QString & moduleName);
      PyObject* loadArguments(const QVariantList& args);
      PyObject* prepareFunction(PyObject* module, const QString& function);
      QVariant prepareOutput(PyObject* pyOutput);
};

#endif // PYTHONINTERFACE_H

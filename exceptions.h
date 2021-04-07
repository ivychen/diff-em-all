#include <string>
#include <iostream>
using namespace std;

/*
    This file contains all the custom exceptions that are used in this library with intelligible error messages
*/

struct NonMatchingFileFormat : public exception
{

    string m_msg;
    public:

    NonMatchingFileFormat(const string &f1, const string &f2)
        : m_msg(std::string("The file formats of : ") + f1 + " "+ f2 + " don't match")
    {}

    virtual const char* what() const throw()
    {
        return m_msg.c_str();
    }

};

struct OperationNotSupported : public exception
{

    virtual const char* what() const throw()
    {
        return "This operation is not supported for the given file formats";
    }

};

struct FileDoesntExist : public exception
{
    string m_msg;

    public:
    FileDoesntExist(const string &fname)
        : m_msg(std::string("The file formats of : ") + fname + " "+  " don't match")
    {}

    virtual const char* what() const throw()
    {
        return m_msg.c_str();
    }

};
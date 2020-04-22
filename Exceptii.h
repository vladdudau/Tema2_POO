#ifndef EXCEPTII_H_INCLUDED
#define EXCEPTII_H_INCLUDED
#include <exception>
using namespace std;
const double oo = (1 << 30);
class Exception:public std::exception
{
private:
    const char* exceptie;
public:
    Exception(const char* copie_exceptie) noexcept
    {
        this->exceptie=copie_exceptie;
    }
    Exception(const Exception&) noexcept=default;
    Exception& operator=(const Exception&) noexcept=default;
    virtual ~Exception() noexcept=default;
    virtual const char* what() const noexcept
    {
        return exceptie;
    }
};


#endif // EXCEPTII_H_INCLUDED

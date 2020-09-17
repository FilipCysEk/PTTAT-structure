//
// Created by krzysiu on 11.07.2020.
//

#ifndef TRAMHOLDUP_EXCEPTION_H
#define TRAMHOLDUP_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class GenericException : public exception {
private:
    string _msg;
    unsigned short errorLevel;
public:
    static const unsigned short CRITICAL_ERROR_END_PROGRAM = 0,
            CRITICAL_ERROR = 1,
            ERROR_TRY_REPEAT = 2,
            ERROR_CONTINUE = 3,
            ERROR_SKIP = 4,
            ERROR = 5;

    GenericException(const string &msg, unsigned short errorLevel) : _msg(msg), errorLevel(errorLevel) {
        if (errorLevel == CRITICAL_ERROR_END_PROGRAM) {
            exit(1);
        }
    }

    GenericException(const string &msg, unsigned short errorLevel, int returnCode) : _msg(msg), errorLevel(errorLevel) {
        if (errorLevel == CRITICAL_ERROR_END_PROGRAM) {
            exit(returnCode);
        }
    }

    virtual const char *what() const noexcept override {
        return _msg.c_str();
    }

    string msg() const noexcept {
        return _msg;
    }

    unsigned short getErrorLevel() const noexcept {
        return errorLevel;
    }

    /**
     * Call passed function (as lambda) passed times. When passed function throw exception with level between
     * ERROR_TRY_REPEAT and level (default (ERROR_TRY_REPEAT))
     * @tparam Function function as lambda calling method
     * @param fun function to call
     * @param times how many times try repeat call function (default 10)
     * @param level Error level between trying repeat call the function. If 0 try to successful.
     * @return function value
     * @throw GenericException with level ERROR if calls unsuccessfully function more than passed times. If function throw error from behind repeat levels it was throwed from this function.
     * @throws GenericException with status higher than passed level or lower, than ERROR_TRY_REPEAT.
     */
    template<typename Function>
    static auto
    tryRunFunction(Function fun, unsigned times = 0, unsigned short level = ERROR_TRY_REPEAT) {
        unsigned counter = 0;

        while (1) {
            try {
                return fun();
            } catch (GenericException &e) {
                if (e.getErrorLevel() >= ERROR_TRY_REPEAT && e.getErrorLevel() <= level) {
                    if (times != 0 && counter > times) {
                        throw GenericException("Throws exception after the max try to call.", ERROR);
                    }
                    ++counter;
                } else {
                    throw GenericException("Function throw error: " + e.msg(), e.getErrorLevel());
                }
            }
        }
    }

    /**
     * Call passed function (as lambda) passed times. When passed function throw exception with level between
     * ERROR_TRY_REPEAT and level (default (ERROR_TRY_REPEAT))
     * @tparam Function function as lambda calling method
     * @tparam CatchFunction function as lambda calling on repeat
     * @param fun function to call. fun(ClassThis)
     * @param catchFun function calling at repeating. catchFun(int tryCount, int maxTry, ClassThis); tryCount - actual try number, maxTry - maximum of avalible try's
     * @param times how many times try repeat call function (default 10)
     * @param level Error level between trying repeat call the function. If 0 try to successful.
     * @return function value
     * @throw GenericException with level ERROR if calls unsuccessfully function more than passed times. If function throw error from behind repeat levels it was throwed from this function.
     * @throws GenericException with status higher than passed level or lower, than ERROR_TRY_REPEAT.
     */
    template<typename Function, typename CatchFunction>
    static auto
    tryRunFunctionCF(Function fun, CatchFunction catchFun, unsigned times = 0,
                     unsigned short level = ERROR_TRY_REPEAT) {
        unsigned counter = 0;

        while (1) {
            try {
                return fun();
            } catch (GenericException &e) {
                if (e.getErrorLevel() >= ERROR_TRY_REPEAT && e.getErrorLevel() <= level) {
                    catchFun(counter, times);
                    if (times != 0 && counter > times) {
                        throw GenericException("Throws exception after the max try to call.", ERROR);
                    }
                    ++counter;
                } else {
                    throw GenericException("Function throw error: " + e.msg(), e.getErrorLevel());
                }
            }
        }
    }

};

#endif //TRAMHOLDUP_EXCEPTION_H

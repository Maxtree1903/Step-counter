#ifndef STEPCOUNTERALGO_H
#define STEPCOUNTERALGO_H

#include <QLabel>
#include <QObject>
#include <QtTest/QTest>
#include <QAccelerometer>
#include <cmath>
#include <thread>
#include <chrono>


class StepCounterAlgo
{
private:
    QAccelerometer sensor;
    int steps;
    QLabel *output;
    bool checkButton;

public:
    StepCounterAlgo(QLabel*& output);
    int NumberOfSteps(){return steps;}
    bool getCheckButton(){return checkButton;}
    void setCheckButton(bool& check);
    void run();
    void calculate(std::vector<std::chrono::duration<double,std::milli>> time,
                   std::vector<qreal> aX, std::vector<qreal> aY, std::vector<qreal> aZ);
    void reset(){steps = 0;}
};

#endif // STEPCOUNTERALGO_H

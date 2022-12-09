#include "stepcounteralgo.h"

StepCounterAlgo::StepCounterAlgo(QLabel *&output): checkButton(true)
{
    steps =0;

    this->output=output;
    sensor.connectToBackend();
    sensor.setProperty("alwaysOn",true);
    sensor.start();
}

void StepCounterAlgo::run()
{
    while(checkButton)
    {
        std::vector<std::chrono::duration<double,std::milli>> moment(100);
        std::vector<qreal> aX(100),aY(100),aZ(100);
        auto start = std::chrono::high_resolution_clock::now();
        for(int i =0;i<100;i++)
        {

            aX[i]=sensor.reading()->x();
            aY[i]=sensor.reading()->y();
            aZ[i]=sensor.reading()->z();
            auto finish = std::chrono::high_resolution_clock::now();
            moment[i] = finish - start;
            QTest::qSleep(15);
        }
        std::thread calcThread(&StepCounterAlgo::calculate, this,
                               std::move(moment), std::move(aX), std::move(aY), std::move(aZ));
        calcThread.detach();
    }

}

void StepCounterAlgo::calculate(std::vector<std::chrono::duration<double,std::milli>> time,
                                std::vector<qreal> aX, std::vector<qreal> aY, std::vector<qreal> aZ)
{
    qreal  aAllAvg=0, eps=0,aXavg=0,aYavg=0,aZavg=0;
    std::vector<qreal> aAll(100), aFinalMax(5), aFinal(100);

    std::vector<std::chrono::duration<double,std::milli>> timeOfMax(6);

    int timeIndex=0;

    timeOfMax[0]=time[0];

    for(int i = 0; i < aX.size(); i++)
    {
        aAll[i]=sqrt(aX[i]*aX[i]+aY[i]*aY[i]+aZ[i]*aZ[i]);
        aAllAvg+=aAll[i];
    }
    aAllAvg/=100;

    for(int i = 0; i < aAll.size(); i++)
    {
        aFinal[i]=aAll[i] - aAllAvg;
    }

    for(int i = 20; i < aFinal.size()+1; i += 20)
    {
        timeIndex = std::distance(aFinal.begin(),std::max_element(aFinal.begin()+i-20,aFinal.begin()+i-1));
        timeOfMax[(i/20)] = time[timeIndex];
        aFinalMax[(i/20)-1] = aFinal[timeIndex];
        aXavg+=*std::max_element(aX.begin()+i-20,aX.begin()+i-1);
        aYavg+=*std::max_element(aY.begin()+i-20,aY.begin()+i-1);
        aZavg+=*std::max_element(aZ.begin()+i-20,aZ.begin()+i-1);

    }

    aXavg/=5;aYavg/=5;aZavg/=5;

    eps = abs(aXavg+aYavg+aZavg)/35;

    for(int i =0;i<aFinalMax.size();i++)
        if(aFinalMax[i]>eps && abs(timeOfMax[i].count()-timeOfMax[i+1].count())>170)
            steps++;

    output->setText("Steps: " +QString::number(steps));
}

void StepCounterAlgo::setCheckButton(bool& check)
{
    checkButton = check;
}



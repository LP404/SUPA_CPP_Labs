#include <string>
#include <vector>
#include <numeric>
#include "gnuplot-iostream.h"

#pragma once //Replacement for IFNDEF

class FiniteFunction{

public:
  FiniteFunction(); //Empty constructor
  FiniteFunction(double range_min, double range_max, std::string outfile); //Variable constructor
  ~FiniteFunction(); //Destructor
  double rangeMin(); //Low end of the range the function is defined within
  double rangeMax(); //High end of the range the function is defined within
  double integral(int Ndiv = 1000); 
  std::vector< std::pair<double,double> > scanFunction(int Nscan = 1000); //Scan over function to plot it (slight hack needed to plot function in gnuplot)
  void setRangeMin(double RMin);
  void setRangeMax(double RMax);
  void setOutfile(std::string outfile);
  void plotFunction(); //Plot the function using scanFunction
  
  //Plot the supplied data points (either provided data or points sampled from function) as a histogram using NBins
  void plotData(std::vector<double> &points, int NBins, bool isdata=true); //NB! use isdata flag to pick between data and sampled distributions
  virtual void printInfo(); //Dump parameter info about the current function (Overridable)
  virtual double callFunction(double x); //Call the function with value x (Overridable)

  //Protected members can be accessed by child classes but not users
protected:
  double m_RMin;
  double m_RMax;
  double m_Integral;
  int m_IntDiv = 0; //Number of division for performing integral
  std::string m_FunctionName;
  std::string m_OutData; //Output filename for data
  std::string m_OutPng; //Output filename for plot
  std::vector< std::pair<double,double> > m_data; //input data points to plot
  std::vector< std::pair<double,double> > m_samples; //Holder for randomly sampled data 
  std::vector< std::pair<double,double> > m_function_scan; //holder for data from scanFunction (slight hack needed to plot function in gnuplot)
  bool m_plotfunction = false; //Flag to determine whether to plot function
  bool m_plotdatapoints = false; //Flag to determine whether to plot input data
  bool m_plotsamplepoints = false; //Flag to determine whether to plot sampled data 
  double integrate(int Ndiv);
  std::vector< std::pair<double, double> > makeHist(std::vector<double> &points, int Nbins); //Helper function to turn data points into histogram with Nbins
  void checkPath(std::string outstring); //Helper function to ensure data and png paths are correct
  void generatePlot(Gnuplot &gp); 
  
private:
  double invxsquared(double x); //The default functional form
};



class Ex34Functions : public FiniteFunction{
    public:
        
        std::vector<double> ReadFunc(std::string fName); 

        Ex34Functions(); //Empty constructor
        Ex34Functions(double range_min, double range_max, std::string outfile); //Variable constructor
        ~Ex34Functions(); //Destructor
        
        int selectDist;

        double callFunction(double x) override;                 
        double Gaussian(double x);           
        double CauchyLorentz(double x);                
        double CrystalBall(double x); 

        void SetGaussParams(double Rmu,double Rstd);
        void SetCauchLorParams(double Rx0,double Rgamma);
        void SetCrystalParams(double Ralpha,double Rn, double Rstd);

        void SetCrystalAverage(double Ravg);

        void printInfo() override;

        double Metropolis(double xOld, double Met_mu, double Met_stdDev);

        std::vector<double> VectorMaker(int N);

        

    private:

        double gdistMu();
        double gdistStandardDev();

        double CoLoX0();
        double CoLoGamma();

        double crystAlpha(); 
        double crystn(); 
        double crystStanDev();
        double crystalAverage();

        void SetCoefs(double Ralpha, double Rn, double RstDev);

        std::tuple<double, double, double, double, double> crystCoeff();              
        
        double m_Mu;
        double m_StdDev;
        double m_x0;
        double m_Gamma;
        double m_stanDev;
        double m_Alpha;
        double m_Average;
        double m_n;
        double m_A;
        double m_B;
        double m_C;
        double m_D;
        double m_N;
        double Met_mu;
        double Met_stdDev;


};
#include <string>
#include <vector>
#include <cmath>
#include "gnuplot-iostream.h"

#pragma once //Replacement for IFNDEF

std::vector<double> ReadFunc(std::string fName); 

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
  double callFunction(double x); //Call the function with value x (Overridable) <- No need - LP

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

class GaussFunction : public FiniteFunction {
public:
    GaussFunction(); // Empty constructor
    GaussFunction(double mean, double stddev, double range_min, double range_max, std::string outfile); // Variable constructor
    ~GaussFunction(); // Destructor
    double callFunction(double x, double mean, double std); 
    void printInfo() override; // Override print function to provide Gaussian specific info

private:
    double m_Mean;
    double m_StdDev;
    double Gauss(double x, double mean, double std);
};

class CauchyLorentzFunction : public FiniteFunction {
public:
    CauchyLorentzFunction(); // Empty constructor
    CauchyLorentzFunction(double location, double scale, double range_min, double range_max, std::string outfile); // Variable constructor
    ~CauchyLorentzFunction(); // Destructor
    double callFunction(double x); // Override the function evaluation for a Gaussian
    void printInfo() override; // Override print function to provide Cauchy-Lorentz specific info

private:
    double m_Mean;
    double m_StdDev;
    double CaLo(double x);
};


class CrystalBallFunction : public FiniteFunction {
public:
    CrystalBallFunction(); // Empty constructor
    CrystalBallFunction(double mean, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile); // Variable constructor
    ~CrystalBallFunction(); // Destructor
    double callFunction(double x); // Override the function evaluation for a Gaussian
    void printInfo() override; // Override print function to provide Crystal Ball specific info

private:
    double m_Mean;
    double m_Sigma;
    double m_Alpha;
    double m_n;
    double Cryst(double x);
};
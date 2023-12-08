#include <string>
#include <vector>
#include <cmath>
#include <tuple>
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
  virtual double integral(int Ndiv = 1000); 
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
  virtual double integrate(int Ndiv);
  std::vector< std::pair<double, double> > makeHist(std::vector<double> &points, int Nbins); //Helper function to turn data points into histogram with Nbins
  void checkPath(std::string outstring); //Helper function to ensure data and png paths are correct
  void generatePlot(Gnuplot &gp); 
  
private:
  double invxsquared(double x); //The default functional form
};

class GaussFunction : public FiniteFunction {
public:
    double gdistMu(); //Low end of the range the function is defined within
    double gdistStandardDev(); //High end of the range the function is defined within
    void setMu(double Rmu);
    void setStandardDev(double Rstd);
    GaussFunction(); // Empty constructor
    GaussFunction(double range_min, double range_max, double mu, double standev,std::string outfile); // Variable constructor
    ~GaussFunction(); // Destructor
    double callFunction(double x) override; 
    void printInfo() override; 
    double integral(int Ndiv = 1000) override;


private:
    double m_Mu;
    double m_StdDev;
    double Gauss(double x);
    double integrate(int Ndiv) override;
};

class CauchyLorentzFunction : public FiniteFunction {
public:
    double CoLoX0(); //Low end of the range the function is defined within
    double CoLoGamma(); //High end of the range the function is defined within
    void setX0(double Rx0);
    void setGamma(double Rgamma);
    CauchyLorentzFunction(); // Empty constructor
    CauchyLorentzFunction(double range_min, double range_max, double x0, double gamma,std::string outfile); // Variable constructor
    ~CauchyLorentzFunction(); // Destructor
    double callFunction(double x) override;  
    void printInfo() override; 

private:
    double m_x0;
    double m_Gamma;
    double CaLo(double x);
    double integrate(int Ndiv) override;
};


class CrystalBallFunction : public FiniteFunction {

    void SetCrystAlpha(double Ralpha); //Low end of the range the function is defined within
    void SetCrystn(double Rn); //High end of the range the function is defined within
    void SetCrystStanDev(double RstDev); //High end of the range the function is defined within
    void SetCoefs(double Ralpha, double Rn, double RstDev);

    double crystAlpha(); //Low end of the range the function is defined within
    double crystn(); //High end of the range the function is defined within
    double crystStanDev(); //High end of the range the function is defined within
    std::tuple<double, double, double, double, double> crystCoeff();

    CrystalBallFunction(); // Empty constructor
    CrystalBallFunction(double alpha, double n, double stdDev,double range_min, double range_max, std::string outfile); // Variable constructor
    ~CrystalBallFunction(); // Destructor
    double callFunction(double x) override; // Override the function evaluation for a Gaussian
    void printInfo() override; // Override print function to provide Crystal Ball specific info

private:
    double m_stanDev;
    double m_Alpha;
    double m_n;
    double m_A;
    double m_B;
    double m_C;
    double m_D;
    double m_N;
    double Cryst(double x);
    double integrate(int Ndiv) override;
};
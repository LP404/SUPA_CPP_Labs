#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//initialised constructor
GaussFunction::GaussFunction(double range_min, double range_max, double mu, double standev,std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Mu = mu;
  m_StdDev = standev;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//initialised constructor
CauchyLorentzFunction::CauchyLorentzFunction(double range_min, double range_max, double x0, double gamma,std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_x0 = x0;
  m_Gamma = gamma;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//initialised constructor
CrystalBallFunction::CrystalBallFunction(double alpha, double n, double stdDev,double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Alpha = alpha;
  m_n = n;
  m_stanDev = stdDev;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}



//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

GaussFunction::~GaussFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

CauchyLorentzFunction::~CauchyLorentzFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

CrystalBallFunction::~CrystalBallFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

void GaussFunction::setMu(double Rmu) {m_Mu = Rmu;};
void GaussFunction::setStandardDev(double Rstd) {m_StdDev = Rstd;};

void CauchyLorentzFunction::setX0(double Rx0) {m_x0 = Rx0;};
void CauchyLorentzFunction::setGamma(double Rgamma) {m_Gamma = Rgamma;};

void CrystalBallFunction::SetCrystAlpha(double Ralpha) {m_Alpha = Ralpha;}; 
void CrystalBallFunction::SetCrystn(double Rn) {m_n = Rn;}; 
void CrystalBallFunction::SetCrystStanDev(double RstDev) {m_stanDev = RstDev;}; 
void CrystalBallFunction::SetCoefs(double Ralpha, double Rn, double RstDev){

m_A = (pow((Rn/Ralpha),Rn))*exp(-((Ralpha*Ralpha)/2));
m_B = (Rn/Rn)-Ralpha;
m_C = (Rn/Ralpha)*(1/(Rn-1))*exp(-((Ralpha*Ralpha)/2));
m_D = sqrt(M_PI_2)*(1+std::erf(Rn/sqrt(2)));
m_N = 1/(RstDev*(m_C+m_D));

};

/*
###################
//Getters
###################
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

double GaussFunction::gdistMu() {return m_Mu;};
double GaussFunction::gdistStandardDev() {return m_StdDev;};

double CauchyLorentzFunction::CoLoX0() {return m_x0;};
double CauchyLorentzFunction::CoLoGamma() {return m_Gamma;};


double CrystalBallFunction::crystAlpha() {return m_Alpha;}; 
double CrystalBallFunction::crystn() {return m_n;}; 
double CrystalBallFunction::crystStanDev() {return m_stanDev;};
std::tuple<double, double, double, double, double> CrystalBallFunction::crystCoeff() {
  return std::tuple<double, double, double, double, double>{m_A, m_B, m_C, m_D, m_N};};




/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);}; //(overridable)

double GaussFunction::Gauss(double x) {
return (1.0/(gdistStandardDev()*(sqrt(2*M_PI))))*exp((-1.0/2.0)*(((x-gdistMu())/gdistStandardDev())*((x-gdistMu())/gdistStandardDev())));  
};
double GaussFunction::callFunction(double x) {return this->Gauss(x);}; //(overridable)

double CauchyLorentzFunction::CaLo(double x) {
   return (1.0/(M_PI*CoLoGamma()*(1.0+(((x-CoLoX0())/CoLoGamma())*((x-CoLoX0())/CoLoGamma())))));
};
double CauchyLorentzFunction::callFunction(double x) {return this->CaLo(x);}; //(overridable)

//This is probably very inefficent

double CrystalBallFunction::Cryst(double x) {
      double average;
      double a;
      double b;
      double A;
      double B;
      double C;
      double D;
      double N;

      auto crstCoeffs = crystCoeff();
        A = std::get<0>(crstCoeffs);
        B = std::get<1>(crstCoeffs);
        C = std::get<2>(crstCoeffs);
        D = std::get<2>(crstCoeffs);
        N = std::get<2>(crstCoeffs);

      ///The average of an evenly space distrubtion should be equal to the sum of the start and end / 2
      b = rangeMax();
      a = rangeMin();

      average = (b+a) / 2;

    if (((x-average)/crystStanDev()) <= -crystAlpha()){
        return (A*pow((B-((x-average)/crystStanDev())),-crystn()));
    } else {
        return (exp(-((x-average)*(x-average))/(2*crystStanDev()*crystStanDev())));
    }
};

double CrystalBallFunction::callFunction(double x) {return this->Cryst(x);}; //(overridable)

/*
###################
Integration by hand (output needed to normalise function when plotting)
###################
*/ 
double FiniteFunction::integrate(int Ndiv){ //private
  double delX;
  double x;
  double Sum;
  Sum = 0.0;
  x = rangeMin();
  delX = (rangeMax() - rangeMin()) / static_cast<double>(Ndiv);
  while(x <= rangeMax()){
    if(x == rangeMin()){
      Sum += 2.0 * callFunction(x);
    }
    else if(x >= rangeMax()){
      Sum += 2.0 * callFunction(x);
    }
    else{
      Sum += callFunction(x);
    }
    x += delX;
  }
  return (delX/2) * Sum;  
}

double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

double GaussFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

double GaussFunction::integrate(int Ndiv){ //private
  double delX;
  double x;
  double Sum;
  Sum = 0.0;
  x = rangeMin();
  delX = (rangeMax() - rangeMin()) / static_cast<double>(Ndiv);
  while(x <= rangeMax()){
    if(x == rangeMin()){
      Sum += 2.0 * callFunction(x);
    }
    else if(x >= rangeMax()){
      Sum += 2.0 * callFunction(x);
    }
    else{
      Sum += callFunction(x);
    }
    x += delX;
  }
  return (delX/2) * Sum;  
}


double CauchyLorentzFunction::integrate(int Ndiv){ //private
  double delX;
  double x;
  double Sum;
  Sum = 0.0;
  x = rangeMin();
  delX = (rangeMax() - rangeMin()) / static_cast<double>(Ndiv);
  while(x <= rangeMax()){
    if(x == rangeMin()){
      Sum += 2.0 * callFunction(x);
    }
    else if(x >= rangeMax()){
      Sum += 2.0 * callFunction(x);
    }
    else{
      Sum += callFunction(x);
    }
    x += delX;
  }
  return (delX/2) * Sum;  
}

double CrystalBallFunction::integrate(int Ndiv){ //private
  double delX;
  double x;
  double Sum;
  Sum = 0.0;
  x = rangeMin();
  delX = (rangeMax() - rangeMin()) / static_cast<double>(Ndiv);
  while(x <= rangeMax()){
    if(x == rangeMin()){
      Sum += 2.0 * callFunction(x);
    }
    else if(x >= rangeMax()){
      Sum += 2.0 * callFunction(x);
    }
    else{
      Sum += callFunction(x);
    }
    x += delX;
  }
  return (delX/2) * Sum;  
}



/*
###################
//Data Read In 
###################
*/

std::vector<double> ReadFunc(std::string fName){

///Opens a file, ready for reading in data
std::ifstream myInput(fName);

///Checks if this file is open, terminates function if that is not the case. Notifies user
if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    exit(1);
}

///Initilises variables that will be used to store data
double valHold;
std::vector<double> val;
std::string strHold;
std::string line;

///Reads in each data from each line, seperated by the comma
///The first loop will read in data but not assign the strings to anything
///Appends data to two vectors, while converting the string it reads in, to a float
while(getline(myInput,line)){
    //The loop will 'discard' the string values
    std::stringstream findLine(line);
    getline(findLine,strHold);
    val.push_back(std::stod(strHold));
}

///Closes the file and returns values out of the fucntion
myInput.close();
return val;
}












/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

void GaussFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

void CauchyLorentzFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

void CrystalBallFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}


/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins-1){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}

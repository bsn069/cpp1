#pragma once

namespace N_Bsn
{
 
D_inline 
T_bool 
IsZero(double val)
{
	return ((-0.000001 < val) && (val < 0.000001) );
}

//returns a random integer between x and y
inline int   RandInt(int x,int y) {return rand()%(y-x+1)+x;}
//returns a random double between zero and 1
inline double RandFloat()      {return ((rand())/(RAND_MAX+1.0));}
inline double RandInRange(double x, double y)
{
  return x + RandFloat()*(y-x);
}
//returns a random bool
inline bool   RandBool()
{
  if (RandInt(0,1)) return true;

  else return false;
}

//returns a random double in the range -1 < n < 1
inline double RandomClamped()    {return RandFloat() - RandFloat();}

//returns a random number with a normal distribution. See method at
//http://www.taygeta.com/random/gaussian.html
inline double RandGaussian(double mean = 0.0, double standard_deviation = 1.0)
{				        
	double x1, x2, w, y1;
	static double y2;
	static int use_last = 0;

	if (use_last)		        /* use value from previous call */
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do 
    {
			x1 = 2.0 * RandFloat() - 1.0;
			x2 = 2.0 * RandFloat() - 1.0;
			w = x1 * x1 + x2 * x2;
		}
    while ( w >= 1.0 );

		w = sqrt( (-2.0 * log( w ) ) / w );
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return( mean + y1 * standard_deviation );
}




//rounds a double up or down depending on its value
inline int Rounded(double val)
{
  int    integral = (int)val;
  double mantissa = val - integral;

  if (mantissa < 0.5)
  {
    return integral;
  }

  else
  {
    return integral + 1;
  }
}


template <class T>
inline double Average(const std::vector<T>& v)
{
  double average = 0.0;
  
  for (unsigned int i=0; i < v.size(); ++i)
  {    
    average += (double)v[i];
  }

  return average / (double)v.size();
}

} // end namespace NBSN

 
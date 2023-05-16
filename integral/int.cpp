#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

double f(double x) noexcept
{
    return sin(1 / (6 - 2 * x));
}

void calculate (double& sum, double leftBorder, double rightBorder, double precision) noexcept
{
    double dx = sqrt(precision);
    double prevsum = sum + 1000;
    double i{};
    
    while (fabs(prevsum - sum) > precision)
    {
        prevsum = sum;
        sum = 0;
        i = leftBorder;
    
        while (i < rightBorder)
        {
            sum = sum + dx * f(i + dx);
            i += dx;
        }
        
        dx /= 2;
    }
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        return -1;
    }
    
    int numOfThreads = atoi(argv[1]);
    double precision = atof(argv[2]);
    double leftBorder = 0.0;
    double rightBorder = 2.99;

    if(numOfThreads > 1)
    {
        auto t_start = std::chrono::high_resolution_clock::now();
        std::vector<double> sums(numOfThreads);
        std::vector<std::thread> threads;
        
        for (int i = 0; auto& sum : sums) 
        {
            threads.emplace_back(calculate, std::ref(sum), leftBorder+(rightBorder-leftBorder)/numOfThreads*i, leftBorder+(rightBorder-leftBorder)/numOfThreads*(i+1), precision);
            ++i;
        }

        for(auto& t: threads)
        {
            t.join();
        }
        
        auto t_end = std::chrono::high_resolution_clock::now();
        std::cout << "Time is: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << std::endl;
        std::cout << "Result is: " << std::accumulate(sums.begin(), sums.end(), 0.0) << std::endl;
    }
    else
    {
        auto t_start = std::chrono::high_resolution_clock::now();
        double sum{};
        calculate(sum, leftBorder, rightBorder, precision);
        auto t_end = std::chrono::high_resolution_clock::now();
        std::cout << "Time is: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << std::endl;
        std::cout << "Result is: " << sum << std::endl;
    }

    return 0;
}


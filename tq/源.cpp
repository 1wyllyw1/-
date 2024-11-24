#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;

// 日期类
class Date 
{
public:
    int year, month, day,hour,min,type;
    Date(){}
    Date(int type)
    {
        time_t t = std::time(nullptr);
        tm now;
        localtime_s(&now, &t);
        year = now.tm_year + 1900;
        month = now.tm_mon + 1;
        day = now.tm_mday;
        hour = now.tm_hour;
        min = now.tm_min;
        if(type==1)
        {
            std::cout << "当前时间: "
                << (now.tm_year + 1900) << '-'
                << std::setfill('0') << std::setw(2) << (now.tm_mon + 1) << '-'
                << std::setfill('0') << std::setw(2) << now.tm_mday << ' '
                << std::setfill('0') << std::setw(2) << now.tm_hour << ':'
                << std::setfill('0') << std::setw(2) << now.tm_min << ':'
                << std::endl;
        }
    }
   
};
// 天气类
class Weather 
{
private:
    Date timestamp;
    string condition;
    double temperature;
    double humidity;
public:
    Weather(){}
    Weather(Date t, string c, double temp, double hum) : timestamp(t), condition(c), temperature(temp), humidity(hum) {}

    string getCondition() const 
    {
        return condition;
    }
    double getTemperature() const 
    {
        return temperature;
    }
    double getHumidity() const {
        return humidity;
    }
};
// 预报类
class Forecast {
private:
    Date timestamp;
    string condition;
    double temperature;
    double humidity;
    double precipitationProbability;
    double change;
public:
    Forecast(){}
    Forecast(Date t, string c, double temp, double hum, double pp,double ch) : timestamp(t), condition(c), temperature(temp), humidity(hum), precipitationProbability(pp),change(ch) {}
    string getCondition() const 
    {
        return condition;
    }
    double getTemperature() const
    {
        return temperature;
    }
    double getHumidity() const 
    {
        return humidity;
    }
    double getPrecipitationProbability() const 
    {
        return precipitationProbability;
    }
    void advice_and_notice()
    {
        if (precipitationProbability > 0.5) 
        {
            cout << endl << "未来两小时内可能会下雨，请注意带伞" << endl << endl;
        }
        if (change <=-2 )
        {
            cout << endl << "天气逐渐变冷，请注意加衣" << endl << endl;
        }
        if (change > 2)
        {
            cout << endl << "天气逐渐变热，可适当减少衣物" << endl << endl;
        }
        if (precipitationProbability <= 0.1 && condition == "Sunny")
        {
            cout << endl << "未来两小时内天气很好，可正常活动" << endl << endl;
        }
        if (temperature > 35)
        {
            cout << endl << "高温天气注意防晒" << endl << endl;
        }
    }
};

// 天气提供者类
class WeatherProvider 
{
public:
    vector<string> city;

    WeatherProvider()
    {
        city.push_back("北京");
        city.push_back("南京");
        city.push_back("上海");
        city.push_back("重庆");
        city.push_back("哈尔滨");
        city.push_back("广州");
        city.push_back("西安");
    }
    // 这里简化处理，返回一个固定的天气信息
    Weather getCurrentWeather(string cityName) 
    {
        if (cityName == "北京")
        {
            return Weather(Date(1), "Cloudy", 8.7, 67);
        }
        else if (cityName == "南京")
        {
            return Weather(Date(1), "Sunny", 15.0, 52);
        }
        else if (cityName == "上海")
        {
            return Weather(Date(1), "Cloudy", 16.0, 57);
        }
        else if (cityName == "重庆")
        {
            return Weather(Date(1), "Rainy", 12.0, 93);
        }
        else if (cityName == "哈尔滨")
        {
            return Weather(Date(1), "Cloudy", 1.0, 46);
        }
        else if (cityName == "广州")
        {
            return Weather(Date(1), "Sunny", 21.0, 74);
        }
        else if (cityName == "西安")
        {
            return Weather(Date(1), "Rainy", 8.0, 100);
        }                       
    }
    // 这里简化处理，返回一个固定的预报信息
   Forecast getShortTermForecast(string cityName) 
   {
       if (cityName == "北京")
       {
            return Forecast(Date(2), "Partly Cloudy", 7.6, 70, 0.3,-1.1);
       }
       else if (cityName == "南京")
       {
           return Forecast(Date(2), "Sunny", 14.0, 54.0, 0.1,-1);
       }
       else if (cityName == "上海")
       {
           return Forecast(Date(2), "Cloudy", 13.0, 60.0, 0.1, -3);
       }
       else if (cityName == "重庆")
       {
           return Forecast(Date(2), "Rainy", 14.0, 93.0, 0.8, 2);
       }
       else if (cityName == "哈尔滨")
       {
           return Forecast(Date(2), "Cloudy", -2.0, 49.0, 0.1, -3);
       }
       else if (cityName == "广州")
       {
           return Forecast(Date(2), "Sunny", 19.0, 76.0, 0.4, -2);
       }
       else if (cityName == "西安")
       {
           return Forecast(Date(2), "Sunny", 7.0, 100.0, 0.7, -1);
       }
        
    }
};

WeatherProvider provider;

// 城市类
class City {
private:
    int cityId;
    string cityName;
    Weather weatherInfo;
    Forecast forecastInfo;
public:
    City(int id, string name)
    {
        cityId = id;
        cityName = name;
        weatherInfo = provider.getCurrentWeather(cityName);
        forecastInfo = provider.getShortTermForecast(cityName);
    }
    string getname()
    {
        return cityName;
    }
    void update() 
    {
        weatherInfo = provider.getCurrentWeather(cityName);
        forecastInfo = provider.getShortTermForecast(cityName);
    }
    void getWeather() const 
    {
        cout << endl <<"当前的天气状况为："<< weatherInfo.getCondition()<<endl
            << "当前的气温为："  << weatherInfo.getTemperature()<<" 摄氏度" << endl
            << "当前的湿度为："<<weatherInfo.getHumidity()<<"%" << endl
            << endl;
        system("pause");
    }
    void getForecast() const 
    {
        cout << endl << "两小时内的天气状况为：" << forecastInfo.getCondition() << endl
            << "两小时内的气温为：" << forecastInfo.getTemperature() << " 摄氏度" << endl
            << "两小时内的湿度为：" << forecastInfo.getHumidity() << "%" << endl
            << "两小时内的降雨概率为：" << forecastInfo.getPrecipitationProbability() * 100 << "%" << endl
            << endl;
        system("pause");
    }
    void getAdvice_and_notice()
    {
        forecastInfo.advice_and_notice();
        system("pause");
    }
};
// 用户类
class User 
{
private:
    string name;
    vector<City> cities;
public:
    User(string s)  
    {
        name = s;
        ifstream inFile("city.txt"); 
        string line;
        int i = 1;
        if (inFile.is_open()) 
        { 
            while (getline(inFile, line)) 
            { 
                City c = City(i,line);
                cities.push_back(c);
                ++i;
            }
            inFile.close(); 
        }
        else 
        {
            cout << "Unable to open file for reading." <<endl;
        }
    }
    //获取用户名
    string getName()
    {
        return name;
    }
    //添加城市
    void addCity()
    {
        system("cls");
        int n = cities.size();
        cout << "本系统可以查询到的城市：" << endl;
        for (int i = 0; i < provider.city.size(); ++i)
        {
            cout << " " << provider.city[i];
        }
        cout << endl << endl;
        cout << "当前已添加的城市有：" << endl << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << i + 1 << "." << cities[i].getname() << endl;
        }
        cout << endl;
        cout << "请输入想要添加的城市（0：退出当前界面）：" << endl;

        string s;

        bool flag = true;
        bool f = false;
        if (n == 0)
        {
            cin >> s;
            if (s != "0")
            {
                while (!f)
                {
                    int i = 0;
                    for (; i < provider.city.size(); ++i)
                    {
                        if (s == provider.city[i])break;
                    }
                    if (i == provider.city.size())
                    {
                        cout << "查询不到该城市，请重新输入：";
                        cin >> s;
                        if (s == "0")
                        {
                            break;
                        }
                    }
                    else
                        f = true;
                }
                if (s != "0")
                {
                    City city = City(n + 1, s);
                    cities.push_back(city);
                }
            }
        }
        else
        {
            while (flag && n != 0)
            {
                cin >> s;
                if (s == "0")
                {
                    break;
                }
                int i = 0;
                for (; i < n; ++i)
                {

                    if (s == cities[i].getname())
                    {
                        cout << "请勿添加重复的城市！！！" << endl;
                        cout << "请重新输入：" << endl;

                        break;
                    }

                }
                if (i == n)
                {
                    flag = false;
                }
            }
            if (s != "0")
            {
                while (!f)
                {
                    int i = 0;
                    for (; i < provider.city.size(); ++i)
                    {
                        if (s == provider.city[i])break;
                    }
                    if (i == provider.city.size())
                    {
                        cout << "查询不到该城市，请重新输入：";
                        cin >> s;
                        if (s == "0")
                        {
                            break;

                        }
                        
                    }
                    else
                    {
                        f = true;
                    }
                }
                if (s != "0")
                {
                     City city = City(n + 1, s);
                     cities.push_back(city);
                }
            }

        }
    }
    //删除城市
    void removeCity() 
    {
        system("cls");
        int n = cities.size();
        cout << "当前已添加的城市有：" << endl ;
        for (int i = 0; i < n; ++i)
        {
            cout << i + 1 << "." << cities[i].getname() << endl;
        }
        cout<< endl;
        cout << "请输入想要删除的城市序号（0：退出当前界面）：" << endl;
        int t;
        cin >> t;
        
        while (t > n||t<0)
        {
            cout << "超出范围，请重新输入！！！" << endl;
            cin >> t;
        }
        if (t != 0)
            cities.erase(cities.begin() + t - 1);
            
    }
    //查询城市
    void lookup()
    {
        system("cls");
        int n = cities.size();
        cout << "当前已添加的城市有：" << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << i + 1 << "." << cities[i].getname() << endl;
        }
        cout << endl;
        cout << "请输入想要查询的城市序号（0：退出当前界面）：" << endl;
        int t;
        cin >> t;

        while (t > n || t < 0)
        {
            cout << "超出范围，请重新输入！！！" << endl;
            cin >> t;
        }
        if (t != 0)
        {
            City c = cities[t-1];
            c.update();
            c.getWeather();
            c.getForecast();
            c.getAdvice_and_notice();
        }
    } 
    //退出
    void exit()
    {
        ofstream outFile("city.txt"); 

        if (outFile.is_open()) 
        { 
            for(int i=0;i<cities.size();++i)
            {
                outFile << cities[i].getname() << endl;
                
            }
            outFile.close();
        }
        else 
        {
           cout << "Unable to open file for writing." << endl;
        }
        system("cls");
        cout << "Goodbye " << name << endl;
        cout << "Have a nice day" << endl;

    }
    //用户主界面
    void userWindow()
    { 
        cout << "     Welcome to my weather system      " << endl;
        cout << "***************************************" << endl;
        cout << "*          1.城市添加                 *" << endl;
        cout << "*          2.城市删除                 *" << endl;
        cout << "*          3.城市查询                 *" << endl;
        cout << "*          4.退出系统                 *" << endl;
        cout << "***************************************" << endl;
        cout << "请输入选项: " << endl;
    
    }
};

int main() 
{
    cout << "欢迎使用天气查询系统，请输入你的昵称："<<endl;
    string s;
    cin >> s;
    system("cls");
    cout << endl;
    cout << "   Hello " << s << " Welcome to my weather system!!!"<<endl<<endl;
    system("pause");
    User user(s);
    int n = 0;
    while(n != 4)
    { 
        system("cls");
        user.userWindow();
        cin >> n;
        switch (n)
        {
            case 1:user.addCity(); break;
            case 2:user.removeCity(); break;
            case 3:user.lookup();  break;
            case 4: user.exit(); break;
            default:
            {
                cout << "请输入有效数字！" << endl;
            }
        }
    }
}
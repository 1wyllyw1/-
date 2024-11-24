#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;

// ������
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
            std::cout << "��ǰʱ��: "
                << (now.tm_year + 1900) << '-'
                << std::setfill('0') << std::setw(2) << (now.tm_mon + 1) << '-'
                << std::setfill('0') << std::setw(2) << now.tm_mday << ' '
                << std::setfill('0') << std::setw(2) << now.tm_hour << ':'
                << std::setfill('0') << std::setw(2) << now.tm_min << ':'
                << std::endl;
        }
    }
   
};
// ������
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
// Ԥ����
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
            cout << endl << "δ����Сʱ�ڿ��ܻ����꣬��ע���ɡ" << endl << endl;
        }
        if (change <=-2 )
        {
            cout << endl << "�����𽥱��䣬��ע�����" << endl << endl;
        }
        if (change > 2)
        {
            cout << endl << "�����𽥱��ȣ����ʵ���������" << endl << endl;
        }
        if (precipitationProbability <= 0.1 && condition == "Sunny")
        {
            cout << endl << "δ����Сʱ�������ܺã��������" << endl << endl;
        }
        if (temperature > 35)
        {
            cout << endl << "��������ע���ɹ" << endl << endl;
        }
    }
};

// �����ṩ����
class WeatherProvider 
{
public:
    vector<string> city;

    WeatherProvider()
    {
        city.push_back("����");
        city.push_back("�Ͼ�");
        city.push_back("�Ϻ�");
        city.push_back("����");
        city.push_back("������");
        city.push_back("����");
        city.push_back("����");
    }
    // ����򻯴�������һ���̶���������Ϣ
    Weather getCurrentWeather(string cityName) 
    {
        if (cityName == "����")
        {
            return Weather(Date(1), "Cloudy", 8.7, 67);
        }
        else if (cityName == "�Ͼ�")
        {
            return Weather(Date(1), "Sunny", 15.0, 52);
        }
        else if (cityName == "�Ϻ�")
        {
            return Weather(Date(1), "Cloudy", 16.0, 57);
        }
        else if (cityName == "����")
        {
            return Weather(Date(1), "Rainy", 12.0, 93);
        }
        else if (cityName == "������")
        {
            return Weather(Date(1), "Cloudy", 1.0, 46);
        }
        else if (cityName == "����")
        {
            return Weather(Date(1), "Sunny", 21.0, 74);
        }
        else if (cityName == "����")
        {
            return Weather(Date(1), "Rainy", 8.0, 100);
        }                       
    }
    // ����򻯴�������һ���̶���Ԥ����Ϣ
   Forecast getShortTermForecast(string cityName) 
   {
       if (cityName == "����")
       {
            return Forecast(Date(2), "Partly Cloudy", 7.6, 70, 0.3,-1.1);
       }
       else if (cityName == "�Ͼ�")
       {
           return Forecast(Date(2), "Sunny", 14.0, 54.0, 0.1,-1);
       }
       else if (cityName == "�Ϻ�")
       {
           return Forecast(Date(2), "Cloudy", 13.0, 60.0, 0.1, -3);
       }
       else if (cityName == "����")
       {
           return Forecast(Date(2), "Rainy", 14.0, 93.0, 0.8, 2);
       }
       else if (cityName == "������")
       {
           return Forecast(Date(2), "Cloudy", -2.0, 49.0, 0.1, -3);
       }
       else if (cityName == "����")
       {
           return Forecast(Date(2), "Sunny", 19.0, 76.0, 0.4, -2);
       }
       else if (cityName == "����")
       {
           return Forecast(Date(2), "Sunny", 7.0, 100.0, 0.7, -1);
       }
        
    }
};

WeatherProvider provider;

// ������
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
        cout << endl <<"��ǰ������״��Ϊ��"<< weatherInfo.getCondition()<<endl
            << "��ǰ������Ϊ��"  << weatherInfo.getTemperature()<<" ���϶�" << endl
            << "��ǰ��ʪ��Ϊ��"<<weatherInfo.getHumidity()<<"%" << endl
            << endl;
        system("pause");
    }
    void getForecast() const 
    {
        cout << endl << "��Сʱ�ڵ�����״��Ϊ��" << forecastInfo.getCondition() << endl
            << "��Сʱ�ڵ�����Ϊ��" << forecastInfo.getTemperature() << " ���϶�" << endl
            << "��Сʱ�ڵ�ʪ��Ϊ��" << forecastInfo.getHumidity() << "%" << endl
            << "��Сʱ�ڵĽ������Ϊ��" << forecastInfo.getPrecipitationProbability() * 100 << "%" << endl
            << endl;
        system("pause");
    }
    void getAdvice_and_notice()
    {
        forecastInfo.advice_and_notice();
        system("pause");
    }
};
// �û���
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
    //��ȡ�û���
    string getName()
    {
        return name;
    }
    //��ӳ���
    void addCity()
    {
        system("cls");
        int n = cities.size();
        cout << "��ϵͳ���Բ�ѯ���ĳ��У�" << endl;
        for (int i = 0; i < provider.city.size(); ++i)
        {
            cout << " " << provider.city[i];
        }
        cout << endl << endl;
        cout << "��ǰ����ӵĳ����У�" << endl << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << i + 1 << "." << cities[i].getname() << endl;
        }
        cout << endl;
        cout << "��������Ҫ��ӵĳ��У�0���˳���ǰ���棩��" << endl;

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
                        cout << "��ѯ�����ó��У����������룺";
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
                        cout << "��������ظ��ĳ��У�����" << endl;
                        cout << "���������룺" << endl;

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
                        cout << "��ѯ�����ó��У����������룺";
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
    //ɾ������
    void removeCity() 
    {
        system("cls");
        int n = cities.size();
        cout << "��ǰ����ӵĳ����У�" << endl ;
        for (int i = 0; i < n; ++i)
        {
            cout << i + 1 << "." << cities[i].getname() << endl;
        }
        cout<< endl;
        cout << "��������Ҫɾ���ĳ�����ţ�0���˳���ǰ���棩��" << endl;
        int t;
        cin >> t;
        
        while (t > n||t<0)
        {
            cout << "������Χ�����������룡����" << endl;
            cin >> t;
        }
        if (t != 0)
            cities.erase(cities.begin() + t - 1);
            
    }
    //��ѯ����
    void lookup()
    {
        system("cls");
        int n = cities.size();
        cout << "��ǰ����ӵĳ����У�" << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << i + 1 << "." << cities[i].getname() << endl;
        }
        cout << endl;
        cout << "��������Ҫ��ѯ�ĳ�����ţ�0���˳���ǰ���棩��" << endl;
        int t;
        cin >> t;

        while (t > n || t < 0)
        {
            cout << "������Χ�����������룡����" << endl;
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
    //�˳�
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
    //�û�������
    void userWindow()
    { 
        cout << "     Welcome to my weather system      " << endl;
        cout << "***************************************" << endl;
        cout << "*          1.�������                 *" << endl;
        cout << "*          2.����ɾ��                 *" << endl;
        cout << "*          3.���в�ѯ                 *" << endl;
        cout << "*          4.�˳�ϵͳ                 *" << endl;
        cout << "***************************************" << endl;
        cout << "������ѡ��: " << endl;
    
    }
};

int main() 
{
    cout << "��ӭʹ��������ѯϵͳ������������ǳƣ�"<<endl;
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
                cout << "��������Ч���֣�" << endl;
            }
        }
    }
}
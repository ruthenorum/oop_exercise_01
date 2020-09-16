#include <iostream>
#include <cmath>

const double MAX_ANGLE = 2 * M_PI;

class Complex {
private:
    // radius
    double r;
    // angle
    double j;

    void check_bounds(double& angle){
        if (angle > MAX_ANGLE){
            angle -= MAX_ANGLE;
        }
        if (angle < 0.0){
            angle += MAX_ANGLE;
        }
    }

public:
    Complex(double _r, double _j){
        r = _r;
        j = _j;
        check_bounds(j);
    }

    Complex (){
        r = 0;
        j = 0;
    }

    Complex operator +(Complex const &obj){
        double a1 = r * cos(j);
        double b1 = r * sin(j);

        double a2 = obj.r * cos(obj.j);
        double b2 = obj.r * sin(obj.j);

        double a3 = a1 + a2;
        double b3 = b1 + b2;

        double new_r = sqrt(a3 * a3 + b3 * b3);
        double new_j = acos(a3 / new_r);

        return Complex(new_r, new_j);
    }

    Complex operator -(Complex const &obj){
        double new_j = obj.j + M_PI;
        check_bounds(new_j);
        return (*this) + obj;
    }

    Complex operator *(Complex const &obj){
        double new_r = r * obj.r;
        double new_j = j + obj.j;
        check_bounds(new_j);
        return Complex(new_r, new_j);
    }

    Complex operator /(Complex const &obj){
        double new_r = r / obj.r;
        double new_j = j - obj.j;
        check_bounds(new_j);
        return Complex(new_r, new_j);
    }

    bool operator ==(Complex const &obj){
        return r == obj.r && j == obj.j;
    }

    bool operator >(Complex const &obj){
        double a1 = r * cos(j);
        double a2 = obj.r * cos(obj.j);
        return a1 > a2;
    }

    Complex conj(){
        double new_j = -j;
        check_bounds(new_j);
        return Complex(r,new_j);
    }

    double get_r() const{
        return r;
    }

    double get_j() const{
        return j;
    }

};

std::ostream &operator<<(std::ostream &os, Complex const &c) {
    return os << "radius: " << c.get_r() << "  angle: " << c.get_j();
}

double from_degrees_to_rad(double deg){
    return deg * M_PI / 180.0;
}

void help(){
    std::cout << "write exit for exit" << std::endl;
    std::cout << "write help for help" << std::endl;
    std::cout << "write input for input two variables (j in degrees) and action, format \nr1\nj1\nr2\nj2\naction" << std::endl;
    std::cout << "in input mode add - addition, sub - subtraction, mult - multiplication, "
                 "div - division, comp - compare, eq for equal, conj for first number conjugate " << std::endl;
}

int main() {
    std::string cmd;
    help();
    while (true){
        std::cin >> cmd;
        if (cmd == "exit"){
            break;
        }
        else if (cmd == "help"){
            help();
        }
        else if (cmd == "input"){
            double r1,j1,r2,j2;
            std::string action;
            std::cin >> r1;
            std::cin >> j1;
            std::cin >> r2;
            std::cin >> j2;
            std::cin >> action;
            Complex a = {r1,from_degrees_to_rad(j1)};
            Complex b = {r2,from_degrees_to_rad(j2)};

            if (action == "add"){
                std::cout << a + b << std::endl;
            }
            else if (action == "sub"){
                std::cout << a - b << std::endl;
            }
            else if (action == "mult"){
                std::cout << a * b << std::endl;
            }
            else if (action == "div"){
                std::cout << a / b << std::endl;
            }
            else if (action == "comp"){
                std::cout << (a > b) << std::endl;
            }
            else if (action == "eq"){
                std::cout << (a == b) << std::endl;
            }
            else if (action == "conj"){
                std::cout << a.conj() << std::endl;
            }
        }
    }
    return 0;
}

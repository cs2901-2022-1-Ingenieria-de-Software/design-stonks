#include <iostream>
#include <unordered_map>
#include <exception>
#define SIGNAL_RED 0
#define SIGNAL_YELLOW 1
#define SIGNAL_WHITE 2
#define SIGNAL_FAN 3

using namespace std;

class Device{
  	string name;
  	bool status;
public:  	
	// Constructores
    Device(string _name):name{_name},status{false} {}
   // Metodos
   void toggle(){
     this->status = !(this->status);
   }
   // Getters
   bool get_status(){return status;}
   string get_name(){return name;}
};

// Singleton
class Remote{
  inline static Remote* control = nullptr;
  unordered_map<int,Device*> devices;
  Remote(){}
  public:
  // Constructor  	
  static Remote* get_control(){
    if(control == nullptr)
      control = new Remote;
    return control;
  }
  // Destructor
  ~Remote() {}

  // Funciones
    void link_device(int button, Device* device){
      if (devices.find(button) != devices.end()) throw std::runtime_error("Ese boton ya esta linkeado");
      devices[button] = device;        		          
    }
     
  	void unlink_device(int button, Device* device){
      if (devices.find(button) == devices.end()) throw std::runtime_error("Ese boton no esta linkeado");
      devices.erase(button);        		          
    }
  
  	void toggle(int button) {
      if (devices.find(button) == devices.end()) throw std::runtime_error("Ese boton no esta linkeado");
  	  devices[button]->toggle();
    }

  	void show_devices_status(){
      
      for (auto it = devices.begin(); it!= devices.end(); ++it) {
        
        cout << "El dispositivo " << (*(it->second)).get_name() << " esta " <<
          ((*(it->second)).get_status() ? "prendido" : "apagado") << endl;
        
      }
    } 

};


// Main
int main() {
  try {
      // Inicializar
      auto yellow_l = new Device("Yellow Light");
      auto red_l = new Device("Red Light");
      auto white_l = new Device("White Light");
      auto fan= new Device("Fan");

      // Vincular
      auto remote = Remote::get_control();
      remote->link_device(SIGNAL_YELLOW, yellow_l);
      remote->link_device(SIGNAL_RED, red_l);
      remote->link_device(SIGNAL_WHITE, white_l);
      remote->link_device(SIGNAL_FAN, fan);

      // Test
      remote->show_devices_status();
      remote->toggle(SIGNAL_RED);
      remote->toggle(SIGNAL_WHITE);
      remote->toggle(SIGNAL_FAN);
      remote->toggle(SIGNAL_RED);
      cout<<endl;
      remote->show_devices_status();      
    } catch (char const*e) {
      std::cout << e << "\n";
    }
  return 0;
}

#include<bits/stdc++.h>
using namespace std;

class NotificationObserver{
   public:
   virtual ~NotificationObserver(){}
   virtual void update(const string& message)=0;
};

class UserNotificationObserver:public NotificationObserver{
    private:
    string userId;
    public:
    UserNotificationObserver(string id){
        userId=id;
    }

    void update(const string& message){
        cout<<userId<<"Has this notification"<<message<<endl;
    }
};

class NotificationService{
    private:
    map<string,NotificationObserver*>observers;
    static NotificationService *instance;
    NotificationService(){}

    public:

    static NotificationService *getInstance(){
        if(!instance){
            instance=new NotificationService();
        }

        return instance;
    }

    void registerObserver(const string& userId, NotificationObserver *observer){
        observers[userId]=observer;
    }

    void removeObserver(const string& userId){
        observers.erase(userId);
    }

    void notifyUser(const string&userId, string content){
        if(observers.find(userId)!=observers.end())
        observers[userId]->update(content);
    }

    void notifyAll(string content){
        for(auto it: observers){
            it.second->update(content);
        }
    }
};

NotificationService *NotificationService::instance=nullptr;

enum class Gender{
    MALE,
    FEMALE,
    NON_BINARY,
    OTHER
};

class Location{
    private:
    double latitude;
    double longitude;

    public:
    Location(){
        latitude=0.0;
        longitude=0.0;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLogitude() const {
        return longitude;
    }

    void setLatitude(double lat){
        latitude=lat;
    }

    void setLogitude(double log){
        longitude=log;
    }

    double distanceInKm(const Location &other) const {
    const double earthRadiusKm = 6371.0;
    const double PI = acos(-1);
    double dLat = (other.latitude - latitude) * PI / 180.0;
    double dLon = (other.longitude - longitude) * PI / 180.0;
        
    double a = sin(dLat/2) * sin(dLat/2) +
           cos(latitude * PI / 180.0) * cos(other.latitude * PI / 180.0) *
           sin(dLon/2) * sin(dLon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        return earthRadiusKm * c;
    }
};

class Interest{
    private:
    string name;
    string category;

    public:
    Interest(string n, string c){
        name=n;
        category=c;
    }

    string getName(){
        return name;
    }

    string getCategory(){
        return category;
    }
};

class Preference{
    private:
    int minAge;
    int maxAge;
    double maxDist;
    vector<string>interests;
    vector<Gender>interestedGender;

    public:
    Preference(){
        minAge=18;
        maxAge=100;
        maxDist=100.0;
    }

    int getminAge(){
        return minAge;
    }

    int getmaxAge(){
        return maxAge;
    }

    int getmaxDist(){
        return maxDist;
    }

    vector<Gender>getInterestedGender(){
        return interestedGender;
    }

    vector<string>getInterest(){
        return interests;
    }

    void setAgeRange(int minage, int maxage){
        minAge=minage;
        maxAge=maxage;
    }

    void setmaxDist(double dist){
        maxDist=dist;
    }

    void addInterestGender(Gender gender){
        interestedGender.push_back(gender);
    }

    void removeInterestGender(Gender gender){
        interestedGender.erase(remove(interestedGender.begin(),interestedGender.end(), gender), interestedGender.end());
    }

    void addInterest(string interest){
       interests.push_back(interest);
    }

    void removeInterest(string interest){
        interests.erase(remove(interests.begin(),interests.end(),interest), interests.end());
    }

    bool isAgeAcceptable(int age){
        return age>minAge && age<=maxAge;
    }

    bool isDistanceAcceptable(double dist){
        return dist<maxDist;
    }

    bool isInterestedInGender(Gender gender){
        for(Gender gen: interestedGender){
            if(gen==gender){
                return true;
            }
        }

        return false;
    }
};

class Message{
    public:
    string senderId;
    string content;
    time_t time_stamp;

    Message(string sender, string message){
        senderId=sender;
        content=message;
        time_stamp=time(nullptr);
    }

    string getSenderId(){
        return senderId;
    }

    string getContent(){
        return content;
    }

    time_t getTimestamp() const {
        return time_stamp;
    }
    
    string getFormattedTime() const {
        struct tm* timeinfo;
        char buffer[80];
        
        timeinfo = localtime(&time_stamp);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }
};

class ChatRoom{
    private:
    string id;
    vector<string>particepantId;
    vector<Message*>messages;

    public:

    ChatRoom(string user1Id, string user2Id, string roomId){
        id=roomId;
        particepantId.push_back(user1Id);
        particepantId.push_back(user2Id);
    }

    ~ChatRoom(){
        for(auto msg: messages){
            delete msg;
        }
    }

    void addMessage(string senderId, string content){
        messages.push_back(new Message(senderId,content));
    }
    
    vector<Message*>getMessages(){
        return messages;
    }

    vector<string>getParticepants(){
        return particepantId;
    }

    string getId(){
        return id;
    }

    bool hasParticepant(string userId){
        return find(particepantId.begin(),particepantId.end(), userId)!=particepantId.end();
    }
    void displayChat() const {
        cout << "===== Chat Room: " << id << " =====" << endl;
        for (const auto& msg : messages) {
            cout << "[" << msg->getFormattedTime() << "] " 
                 << msg->getSenderId() << ": " << msg->getContent() << endl;
        }
        cout << "=========================" << endl;
    }

};

class UserProfile{
    private:
    string name;
    int age;
    Gender gender;
    string bio;
    vector<string>photos;
    vector<Interest*>interests;
    Location loc;

    public:
    UserProfile(){
        name="";
        age=0;
        bio="";
    }

    void setName(string username){
        name=username;
    }

    void setAge(int userAge){
        age=userAge;
    }

    void setGender(Gender usergender){
        gender=usergender;
    }

    void addPhotos(string photopath){
        photos.push_back(photopath);
    }
    void removePhotos(string photopath){
        photos.erase(remove(photos.begin(),photos.end(), photopath), photos.end());
    }
    void addInterest(string name, string category){
        Interest *interest=new Interest(name,category);
        interests.push_back(interest);
    }

    void removeInterest(string name, string category){
        for(auto it: interests){
            if(it->getName()==name && it->getCategory()==category){
                interests.erase(remove(interests.begin(),interests.end(), it), interests.end());
            }
        }
    }

    void setbio(string biography){
        bio=biography;
    }

    void setLocation(Location &location){
        loc=location;
    }

    string getName(){
        return name;
    }

    int getAge(){
        return age;
    }

    Gender getGender(){
        return gender;
    }

    Location getLocation(){
        return loc;
    }

    vector<string>&getPhotos(){
        return photos;
    }

    vector<Interest*>&getInterest(){
        return interests;
    }

    const Location& getLocation() const {
        return loc;
    }

     void display() const {
        cout << "===== Profile =====" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: ";
        switch (gender) {
            case Gender::MALE: cout << "Male"; break;
            case Gender::FEMALE: cout << "Female"; break;
            case Gender::NON_BINARY: cout << "Non-binary"; break;
            case Gender::OTHER: cout << "Other"; break;
        }
        cout << endl;
        
        cout << "Bio: " << bio << endl;
        
        cout << "Photos: ";
        for (const auto& photo : photos) {
            cout << photo << ", ";
        }
        cout << endl;
        
        cout << "Interests: ";
        for (const auto& interest : interests) {
            cout << interest->getName() << " (" << interest->getCategory() << "), ";
        }
        cout << endl;
        
        cout << "Location: " << loc.getLatitude() << ", " << loc.getLogitude() << endl;
        cout << "===================" << endl;
    }
};

enum class SWIPE_ACTION{
    LEFT,
    RIGHT
};

class User{
    private:
    string userId;
    UserProfile *profile;
    Preference *preference;
    map<string,SWIPE_ACTION>swipehistory;
    NotificationObserver *notificationObserver;

    public:

    User(const string& id){
        userId=id;
        profile=new UserProfile();
        preference=new Preference();
        notificationObserver=new UserNotificationObserver(userId);
        NotificationService::getInstance()->registerObserver(userId, notificationObserver);
    }

    ~User() {
        delete profile;
        delete preference;
        NotificationService::getInstance()->removeObserver(userId);
        delete notificationObserver;
    }

    void swipe(string otheruserid, SWIPE_ACTION Action){
        swipehistory[otheruserid]=Action;
    }

    bool hasLiked(string otheruserid){
        if(swipehistory.find(otheruserid)==swipehistory.end()){
            cout<<"No user with this user Id found"<<userId<<endl;
            return false;
        }

        return swipehistory[otheruserid]==SWIPE_ACTION::RIGHT;
    }

    bool hasDisliked(string otheruserid){
        if(swipehistory.find(otheruserid)==swipehistory.end()){
            cout<<"No user with this user Id found"<<otheruserid<<endl;
            return false;
        }

        return swipehistory[otheruserid]==SWIPE_ACTION::LEFT;  
    }

    bool hasInteractedWith(string otheruserid){
         return swipehistory.find(otheruserid)!=swipehistory.end();
    }

    string getUserId(){
        return userId;
    }

    UserProfile *getProfile(){
        return profile;
    }

    Preference *getPreference(){
        return preference;
    }

    void display(){
        profile->display();
    }
};

class LocationStrategy{
    public:
    virtual ~LocationStrategy(){};
    virtual vector<User*>findNearbyUser(Location &location, double maxDist, vector<User*>&allUsers)=0;
};

class BasicLocationStrategy:public LocationStrategy{
    public:
    vector<User*>findNearbyUser(Location &location, double maxDist, vector<User*>&allUsers){
        vector<User*>nearbyusers;
        for(User *user: allUsers){
            double distance=location.distanceInKm(user->getProfile()->getLocation());
            if(distance<=maxDist){
                nearbyusers.push_back(user);
            }
        }

        return nearbyusers;
    }
};

class LocationService{
    private:
    static LocationService *instance;
    LocationStrategy *strat;
    LocationService(){};

    public:

    static LocationService *getInstance(){
        if(!instance){
            instance=new LocationService();
        }

        return instance;
    }

    void setStrategy(LocationStrategy *strategy){
        strat=strategy;
    }

    vector<User*>findNearyByUser(Location location, double maxDist, vector<User*>allUsers){
        return strat->findNearbyUser(location,maxDist,allUsers);
    }
};

LocationService *LocationService::instance=nullptr;

class Matcher{
    public:

    virtual ~Matcher(){}
    virtual double calculateMatchScore(User *user1, User * user2)=0;
};

class BaiscMatcher:public Matcher{
    public:
    
    double calculateMatchScore(User *user1, User *user2) override{
        //check if interested gender aligh

        bool user1InterestedInGenderofuser2=user1->getPreference()->isInterestedInGender(user2->getProfile()->getGender());
        bool user2InterestedInGenderofuser1=user2->getPreference()->isInterestedInGender(user1->getProfile()->getGender());

        if(!user1InterestedInGenderofuser2 || !user2InterestedInGenderofuser1){
            return 0.0;
        }

        //check age preference

        bool user1Likesuser2Age=user1->getPreference()->isAgeAcceptable(user2->getProfile()->getAge());
        bool user2Likesuser1Age=user2->getPreference()->isAgeAcceptable(user1->getProfile()->getAge());

        if(!user1Likesuser2Age || !user2Likesuser1Age){
            return 0.0;
        }

        //check distance preference

        double distance=user1->getProfile()->getLocation().distanceInKm(user2->getProfile()->getLocation());
        bool user1Likesuser2Dist=user1->getPreference()->isDistanceAcceptable(distance);
        bool user2Likesuser1Dist=user2->getPreference()->isDistanceAcceptable(distance);

        if(!user2Likesuser1Dist || !user1Likesuser2Dist){
            return 0.0;
        }

        return 0.5;
    }
};


class InterestBaseMatcher:public Matcher{
    public:

    double calculateMatchScore(User *user1, User *user2) override{
        BaiscMatcher bm;
        double BasicScore=bm.calculateMatchScore(user1, user2);

        if(BasicScore==0.0){
            return 0.0;
        }

        vector<string>SharedInterest;
        for(auto it: user1->getProfile()->getInterest()){
            SharedInterest.push_back(it->getName());
        }

        int commonInterest=0;

        for(auto it: user2->getProfile()->getInterest()){
            if(find(SharedInterest.begin(),SharedInterest.end(), it->getName())!=SharedInterest.end()){
                  commonInterest++;
            }
        }

        double maxInterestScore=max(user1->getProfile()->getInterest().size(), user2->getProfile()->getInterest().size());
        double interestScore=maxInterestScore>0? 0.2*(commonInterest/maxInterestScore):0.0;

        return BasicScore+interestScore;
    }
};

class LocationBasedMatcher:public Matcher{
    public:

    double calculateMatchScore(User *user1, User *user2){
        InterestBaseMatcher interestmatch;
        double interestscore=interestmatch.calculateMatchScore(user1, user2);

        if(interestscore==0.0){
            return 0.0;
        }

        double distance=user1->getProfile()->getLocation().distanceInKm(user2->getProfile()->getLocation());
        double maxDistance=max(user1->getPreference()->getmaxDist(),user2->getPreference()->getmaxDist());

        double proximtyscore=maxDistance>0? 0.2*(1-distance/maxDistance):0.0;

        return interestscore+proximtyscore;
    }
};
enum class MatcherType{
    BASIC,
    INTEREST,
    LOCATION
};

class MatcherFactory{
    public:
    static Matcher *createMatcher(MatcherType type){
        switch(type){
            case MatcherType::BASIC:
              return new BaiscMatcher();

            case MatcherType::INTEREST:
              return new InterestBaseMatcher();
            
            case MatcherType::LOCATION:
               return new LocationBasedMatcher();
        }
    }
};

//singleton
class DatingApp{
    private:
    vector<User*>users;
    vector<ChatRoom*>rooms;
    Matcher *matcher;
    static DatingApp *instance;

    public:

    static DatingApp *getInstance(){
        if(!instance){
            instance=new DatingApp();
        }

        return instance;
    }

    void setMatcher(MatcherType type){
        matcher=MatcherFactory::createMatcher(type);
    }

    User* createUser(string userId){
        User *user=new User(userId);
        users.push_back(user);
    }

    User *getUserById(const string &userId){
        for(User *user:users){
            if(user->getUserId()==userId){
                return user;
            }
        }

        return nullptr;
    }

    vector<User*>findNearbyUser(const string& userId, double maxDist=5.0){
        User *user=getUserById(userId);
        if(user==nullptr){
            return vector<User*>();
        }
     
        vector<User*>nearbyusers=LocationService::getInstance()->findNearyByUser(user->getProfile()->getLocation(),maxDist, users);

        nearbyusers.erase(remove(nearbyusers.begin(),nearbyusers.end(),user),nearbyusers.end());

        vector<User*>filteredUser;

        for(User *otheruser: nearbyusers){
             if(user->hasInteractedWith(otheruser->getUserId())){
                continue;
            }

            double score=matcher->calculateMatchScore(user,otheruser);

            if(score>0.0){
                filteredUser.push_back(otheruser);
            }
        }

        return filteredUser;
    }

    bool swipe(const string& userId, const string& otheruserId, SWIPE_ACTION action){
        User *user=getUserById(userId);
        User *otheruser=getUserById(otheruserId);

        if(!user || !otheruser){
            cout<<"Any of the user do not exist"<<endl;
            return false;
        }

        if(action==SWIPE_ACTION::RIGHT && otheruser->hasLiked(userId)){
            //both are matcher, then create chatroom
            string ChatroomId=userId+"_"+otheruserId;
            ChatRoom *room=new ChatRoom(userId,otheruserId,ChatroomId);
            rooms.push_back(room);

            NotificationService::getInstance()->notifyUser(userId, "You have a new match with " + otheruser->getProfile()->getName() + "!");
            NotificationService::getInstance()->notifyUser(otheruserId, "You have a new match with " + user->getProfile()->getName() + "!");

            return true;
        }

        return false;
    }

    ChatRoom *getChatRoom(const string& userId, const string &otheruserId){
        for(ChatRoom *chatrooms: rooms){
            if(chatrooms->hasParticepant(userId) && chatrooms->hasParticepant(otheruserId)){
                return chatrooms;
            }
        }

        return nullptr;
    }

    void sendMessage(const string& senderId, const string &receiverId, string content){
        ChatRoom *chatroom=getChatRoom(senderId,receiverId);
        if(chatroom==nullptr){
            cout<<"No room with this users found"<<endl;
            return;
        }

        chatroom->addMessage(receiverId,content);

        NotificationService::getInstance()->notifyUser(receiverId, "New message from"+ getUserById(senderId)->getProfile()->getName());
    }

    void displayUser(const string& userId) {
        User* user = getUserById(userId);
        if (user == nullptr) {
            cout << "User not found." << endl;
            return;
        }
        
        user->display();
    }

    void displayChatroom(const string& user1Id, const string& user2Id){
        ChatRoom *room=getChatRoom(user1Id,user2Id);

        if(!room){
            cout<<"No room with this users exist"<<endl;
            return;
        }

        room->displayChat();
    }
};

DatingApp *DatingApp::instance=nullptr;

int main(){
DatingApp* app = DatingApp::getInstance();
    
    // Create users
    User* user1 = app->createUser("user1");
    User* user2 = app->createUser("user2");

    // Set user1 profile
    UserProfile* profile1 = user1->getProfile();
    profile1->setName("Rohan");
    profile1->setAge(28);
    profile1->setGender(Gender::MALE);
    profile1->setbio("I am a software developer");
    profile1->addPhotos("rohan_photo1.jpg");
    profile1->addInterest("Coding", "Programming");
    profile1->addInterest("Travel", "Lifestyle");
    profile1->addInterest("Music", "Entertainment");
    
    // Setup user1 preferences
    Preference* pref1 = user1->getPreference();
    pref1->addInterestGender(Gender::FEMALE);
    pref1->setAgeRange(25, 30);
    pref1->setmaxDist(10.0);
    pref1->addInterest("Coding");
    pref1->addInterest("Travel");
    
    // Setup user2 profile
    UserProfile* profile2 = user2->getProfile();
    profile2->setName("Neha");
    profile2->setAge(27);
    profile2->setGender(Gender::FEMALE);
    profile2->setbio("Art teacher who loves painting and traveling.");
    profile2->addPhotos("neha_photo1.jpg");
    profile2->addInterest("Painting", "Art");
    profile2->addInterest("Travel", "Lifestyle");
    profile2->addInterest("Music", "Entertainment");
    
    // Setup user2 preferences
    Preference* pref2 = user2->getPreference();
    pref2->addInterestGender(Gender::MALE);
    pref2->setAgeRange(27, 30);
    pref2->setmaxDist(15.0);
    pref2->addInterest("Coding");
    pref2->addInterest("Movies");

    // Set location for user1
    Location location1;
    location1.setLatitude(1.01);
    location1.setLogitude(1.02);
    profile1->setLocation(location1);
    
    // Set location for user2 (Close to user1, within 5km)
    Location location2;
    location2.setLatitude(1.03);
    location2.setLogitude(1.04);
    profile2->setLocation(location2);

    // Display user profiles
    std::cout << "---- User Profiles ----" << std::endl;
    app->displayUser("user1");
    app->displayUser("user2");
    
    // Find nearby users for user1 (within 5km)
    std::cout << "\n---- Nearby Users for user1 (within 5km) ----" << std::endl;
    std::vector<User*> nearbyUsers = app->findNearbyUser("user1", 5.0);
    std::cout << "Found " << nearbyUsers.size() << " nearby users" << std::endl;
    for (User* user : nearbyUsers) {
        std::cout << "- " << user->getProfile()->getName() << " (" << user->getUserId() << ")" << std::endl;
    }
    
    // User1 swipes right on User2
    std::cout << "\n---- Swipe Actions ----" << std::endl;
    std::cout << "User1 swipes right on User2" << std::endl;
    app->swipe("user1", "user2", SWIPE_ACTION::RIGHT);
    
    // User2 swipes right on User1 (creating a match)
    std::cout << "User2 swipes right on User1" << std::endl;
    app->swipe("user2", "user1", SWIPE_ACTION::RIGHT);
    
    // Send messages in the chat room
    std::cout << "\n---- Chat Room ----" << std::endl;
    app->sendMessage("user1", "user2", "Hi Neha, Kaise ho?");
    
    app->sendMessage("user2", "user1", "Hi Rohan, Ma bdiya tum btao");
    
    // Display the chat room
    app->displayChatroom("user1", "user2");
    
    return 0;
}





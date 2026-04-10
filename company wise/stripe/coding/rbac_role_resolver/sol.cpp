#include<iostream>
#include<unordered_map>
#include<unordered_set>

using namespace std;


typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<unordered_map<string,string>> vum;
class RbacRoleResolver {
    public:
    RbacRoleResolver() = default;
    RbacRoleResolver(vvs accounts, vvs user_role_assignments) {
        for(auto it : accounts){
            g[it[1]] = it[3];
        }
        for(auto it : user_role_assignments){
            auto userid = it[1], accid = it[3], 
                role = it[5];
            roles[accid][userid] = role;
        }
    }

    void getUserRoles(string userid, string accid){
        vs ans;
        // if(roles.find(accid) == roles.end()) return;
        // if(roles[accid].find(userid) == roles[accid].end()) return;
        // //ans.push_back(roles[accid][userid]);
        ans = getParentRoles(userid,accid);
        if(ans.size()) {
            for(auto it : ans)cout<<it<<" ";
            cout<<endl;
        } else {
            cout<<"No role"<<endl;
        }
    }

    void getUsersForAccount(string accid){
        vs ans;
        unordered_set<string> ss;
        while(g.find(accid) != g.end()){
            for(auto it : roles[accid]) {
                ss.insert(it.first);
            }
            accid = g[accid];
        }
        for(auto it : ss) cout<<it<<" ";
        cout<<endl;
    }

    void getUsersForAccountWithFilter(string accid, vs rolesReq) {
        unordered_set<string> ss(rolesReq.begin(),rolesReq.end());
        unordered_map<string, unordered_set<string>> rolemap;
        while(g.find(accid) != g.end()){
            for(auto it : roles[accid]) {
                if(!ss.empty() && (ss.find(it.second) == ss.end())) continue;
                rolemap[it.first].insert(it.second);
            }
            accid = g[accid];
        }
        for(auto it : rolemap){
            if(ss.empty() || (it.second.size() == ss.size())) cout<<it.first<<" ";
        }
        cout<<endl;
    }

    private:
    unordered_map<string,unordered_map<string,string>> roles;
    unordered_map<string,string> g;

    vs getParentRoles(string userid, string accid){
        vs ans;
        while(g.find(accid) != g.end()){
            auto it = roles.find(accid);
            if(it != roles.end()) {
                 auto it1 = roles[accid].find(userid);
                 if(it1 != roles[accid].end()) {
                    ans.push_back(roles[accid][userid]);
                 }
            }
            accid = g[accid];
        }
        return ans;
    }

};


void testmethod3() {
        vvs accounts = {
            {"accountId", "org_1", "parent", ""},
            {"accountId", "wksp_1", "parent", "org_1"}
            //  {"accountId", "wksp_2", "parent", "org_1"}
            //{"accountId", "team_1", "parent", "wksp_1"}
    };
    vvs arr = {
            {"userId", "usr_1", "accountId", "org_1", "role", "admin"},
            {"userId", "usr_1", "accountId", "wksp_1", "role", "editor"},
            {"userId", "usr_2", "accountId", "wksp_1", "role", "editor"},
            {"userId", "usr_3", "accountId", "wksp_1", "role", "viewer"}
    };
    RbacRoleResolver rbac(accounts,arr);
    rbac.getUsersForAccountWithFilter("wksp_1", {});
    rbac.getUsersForAccountWithFilter("wksp_1", {"admin"});
    rbac.getUsersForAccountWithFilter("wksp_1", {"editor"});
    rbac.getUsersForAccountWithFilter("wksp_1", {"admin", "editor"});
    rbac.getUsersForAccountWithFilter("wksp_1", {"superadmin"});
}

void testmethod2() {
        vvs accounts = {
            {"accountId", "org_1", "parent", ""},
            {"accountId", "wksp_1", "parent", "org_1"},
             {"accountId", "wksp_2", "parent", "org_1"}
            //{"accountId", "team_1", "parent", "wksp_1"}
    };
    vvs arr = {
            {"userId", "usr_1", "accountId", "org_1", "role", "admin"},
            {"userId", "usr_2", "accountId", "wksp_1", "role", "editor"},
            {"userId", "usr_3", "accountId", "wksp_1", "role", "viewer"}
    };
    RbacRoleResolver rbac(accounts,arr);
    rbac.getUsersForAccount("org_1");
    rbac.getUsersForAccount("wksp_1");
    rbac.getUsersForAccount("wksp_2");
}
void testmethod() {
    vvs accounts = {
            {"accountId", "org_1", "parent", ""},
            {"accountId", "wksp_1", "parent", "org_1"},
            // {"accountId", "wksp_2", "parent", "org_1"},
            {"accountId", "team_1", "parent", "wksp_1"}
    };
    vvs arr = {
            {"userId", "usr_1", "accountId", "org_1", "role", "admin"},
        {"userId", "usr_1", "accountId", "wksp_1", "role", "editor"},
        {"userId", "usr_2", "accountId", "wksp_1", "role", "viewer"}
    };
    RbacRoleResolver rbac(accounts,arr);
    rbac.getUserRoles("usr_1", "org_1");
    rbac.getUserRoles("usr_1", "wksp_1");
    rbac.getUserRoles("usr_1", "team_1");
    rbac.getUserRoles("usr_2", "team_1");
    rbac.getUserRoles("usr_2", "org_1");
}

int main(){
    testmethod3();
    return 0;
}
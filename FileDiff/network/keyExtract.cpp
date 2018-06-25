#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <unordered_map>
#include <functional>
using namespace std;

int make_directory(const string& dir){
	const int dir_err = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	return dir_err;
}

#define ASSERT(x) if(!(x)) {printf("%d,error",__LINE__);exit(1);} 

std::hash<std::string> hash_fn;

class Http_response{
	public:
	//string URL;
	vector<string> header;
	string content;
	int count;
	string type;
	unsigned length;

	string to_string(){
		string res = "Response :\n";/*
		if(URL!=""){
			res+="Long-URL: ";
			res+=URL;
		}
		*/
		for(auto& s:header)	{
			res+=s;
			res+='\n';
		}
		res+='\n';
		res+=content;
		return res;
	}
};

string javascript_new_line(const string& in_file){

}

string slash_transform(const string& s){
	string out;
	for(auto c:s){
		if(c=='/'){
			out+='@';
		}else out+=c;
	}
	return out;
}
//return the number of response
int write_response_to_file(vector<string>& out_name,vector<string>& res_vec,vector<string>& file_content,const string& out_path){
	int cur_p = 0;
	vector<Http_response> v_res;
	v_res.push_back(Http_response());
	unordered_map<int,int> res_map;
	bool is_image = false;
	while(cur_p<res_vec.size()){

		while(res_vec[cur_p]!=""){
			if(res_vec[cur_p].find("count")==0){
				//stoi(res_vec[cur_p].substr(8,string::npos));
				v_res[v_res.size()-1].count = stoi(res_vec[cur_p].substr(8,string::npos));
				res_map[v_res[v_res.size()-1].count] = v_res.size();
			}else if(res_vec[cur_p].find("content-type : image")==0){
				is_image = true;
				v_res[v_res.size()-1].header.push_back(res_vec[cur_p]);
			}else
				v_res[v_res.size()-1].header.push_back(res_vec[cur_p]);
			cur_p++;
		}
		cur_p++;
		while(res_vec[cur_p].find("HTTP/")!=0&&cur_p<res_vec.size()){
			if(is_image) {
				cur_p++;
				continue;
			}
			v_res[v_res.size()-1].content+=res_vec[cur_p];
			v_res[v_res.size()-1].content+='\n';
			cur_p++;
			
		}
		is_image = false;
		v_res.push_back(Http_response());
	}
	v_res.pop_back();
	if(v_res.size()!=out_name.size()){
		printf("response number %d not equal request number %d\n",out_name.size(),v_res.size());
		//return -1;
	}
	/*
	int count = 0;

	for(auto &s:out_name){
		file_content[count]+=v_res[count].to_string();

		//ofs.write(v_res[count].to_string().c_str(),v_res[count].to_string().size());
		//ofs.close();

		count++;
	}
*/
	for(int i = 0;i<out_name.size();i++){
		ofstream ofs;
		if(out_name[i].size()>240){
			//v_res[i].URL = out_name[i];
			file_content[i] = string("Long-URL: ")+out_name[i]+"\n"+file_content[i];
			out_name[i] = to_string(hash_fn(out_name[i]));
			//file_content[i].U
		}
		ofs.open(out_path+'/'+slash_transform(out_name[i]),ios_base::out);
		if(!ofs.is_open()){
			printf("%s file cannot open\n",(out_path+out_name[i]).c_str());
		}
		Http_response* out;
		//printf("v_res size is %d\n",v_res.size());
		if(res_map[i] != 0){
			//printf("i = %d\n",res_map[i]);
			out = &v_res[res_map[i]-1];
		}
		ofs.write((file_content[i]+out->to_string()).c_str(),(file_content[i]+out->to_string()).size());
		ofs.close();
	}
	
	return 0;
}

vector<string> file_to_string_vec(){

}
//return the number of request
int make_file(vector<string>& req_vec,vector<string>& out_name,/*const string& folder_name,*/vector<string>& file_content){

	unordered_map<string,int> map;
	ASSERT(out_name.size()==0);

	for(int i = 0;i<req_vec.size();i++){


		string domain_name = req_vec[i];
		i++;
		size_t end_p = req_vec[i].find_first_of('?');
		if(end_p == string::npos){
			end_p = req_vec[i].find_last_of(' ');
		}
		string URL = req_vec[i].substr(req_vec[i].find_first_of('/'),end_p-req_vec[i].find_first_of('/'));
		string name = domain_name+URL;
		string visit_num = to_string(map[name]);
		map[name]++;

		out_name.push_back(name+"_V"+visit_num);
		string content;
		i++;
		while((req_vec[i]!="") || req_vec[i-1]!=""){
			content+=req_vec[i];
			content+='\n';
			i++;
		}
		file_content.push_back(content);
	}

	return out_name.size();
/*

	for(int i = 0;i<req_vec.size();i++){

		if(req_vec[i].find("GET /")==0){


			string URL = req_vec[i].substr(4);
			string name = req_vec[i-1] + URL;
			string visit_num = to_string(map[name]);

			out_name.push_back(name+'-'+visit_num);
			file_content.push_back("");
			
		}else{
			
			file_content[i]+=(req_vec[i]+'\n');
		}
	}
	*/
}


int main(int argc ,char** argv){

	if(argc<4){
		printf("parameter not enough\n");
	}

	const string request_path = argv[1];
	const string response_path = argv[2];
	vector<string> req_vec;
	vector<string> res_vec;
	const string out_path = argv[3];
	vector<string> file_name;
	vector<string> file_content;

	ifstream req(request_path);
	ifstream res(response_path);
	string tmp;

	while(!req.eof()){
		getline(req,tmp);
		req_vec.push_back(tmp);
		tmp.clear();
	}
	req_vec.pop_back();

	while(!res.eof()){
		getline(res,tmp);
		res_vec.push_back(tmp);
		tmp.clear();
	}

	int req_size = make_file(req_vec,file_name,file_content);

	printf("request message size is %d\n",req_size);

	if(write_response_to_file(file_name,res_vec,file_content,out_path)<0){
		printf("write response failed\n");
		return 1;
	}
	return 0;

}

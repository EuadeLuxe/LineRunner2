#include "cfgFile.h"

namespace bb{

cfgFile::cfgFile(){
	root = std::shared_ptr<Node>(new Node("root"));
}

void cfgFile::write(std::ofstream &file, std::shared_ptr<Node> node, std::string tabs){
	for(auto n : node->getChildren()){
		if(n->getType() != Node::TYPE::CLASS){
			if(n->getType() == Node::TYPE::STRING){
				if(n->value.size() == 1){
					file<<tabs<<n->getName()<<" = \""<<escape(n->value[0])<<"\";"<<std::endl;
				}
				else if(n->value.size() > 1){
					file<<tabs<<n->getName()<<" = {";

					for(unsigned int i = 0; i < n->value.size()-1; i++){
						file<<"\""<<escape(n->value[i])<<"\", ";
					}

					file<<"\""<<escape(n->value[n->value.size()-1])<<"\"}"<<std::endl;
				}
				else{
					file<<tabs<<n->getName()<<" = \"\";"<<std::endl;
				}
			}
			else{
				if(n->value.size() == 1){
					file<<tabs<<n->getName()<<" = "<<n->value[0]<<";"<<std::endl;
				}
				else if(n->value.size() > 1){
					file<<tabs<<n->getName()<<" = {";

					for(unsigned int i = 0; i < n->value.size()-1; i++){
						file<<n->value[i]<<", ";
					}

					file<<n->value[n->value.size()-1]<<"}"<<std::endl;
				}
				else{
					file<<tabs<<n->getName()<<" = 0;"<<std::endl;
				}
			}
		}
		else{
			file<<tabs<<n->getName()<<"{"<<std::endl;
			write(file, n, tabs+"\t");
			file<<tabs<<"}"<<std::endl;
		}
	}
}

std::string cfgFile::escape(const std::string &value){
	std::string escaped;

	for(auto c : value){
		if(c == '"'){
			escaped += '\\';
		}

		escaped += c;
	}

	return escaped;
}

cfgFile::Node::TYPE cfgFile::testType(const std::string &value){
	Node::TYPE type = Node::TYPE::STRING;

	for(auto v : value){
		if(!std::isdigit(v) && v != '.'){
			type = Node::TYPE::STRING;

			break;
		}
		else if(type != Node::TYPE::FLOAT){
			type = Node::TYPE::INT;
		}

		if(v == '.'){
			type = Node::TYPE::FLOAT;
		}
	}

	return type;
}

bool cfgFile::read(const std::string &path){
	std::ifstream file(path, std::ifstream::in);

	if(!file.good()){
		return false;
	}

	// parse (throw out) comments
	std::string content, line;
	unsigned int length;
	bool string = false, comment = false;
	char c;

	while(std::getline(file, line)){
		length = line.length();

		for(unsigned int i = 0; i < length; i++){
			c = line.at(i);

			if(!string && c == '"' && (i == 0 || line.at(i-1) != '\\')){ // string start
				string = true;
			}
			else if(string && c == '"' && (i == 0 || line.at(i-1) != '\\')){ // string end
				string = false;
			}

			if(!string && i != length-1){
				if(c == '/' && line.at(i+1) == '/'){ // single line comment
					break;
				}
				else if(c == '*' && line.at(i+1) == '/'){ // multi line comment end
					i++;
					comment = false;

					continue;
				}
				else if(c == '/' && line.at(i+1) == '*'){ // multi line comment start
					comment = true;

					continue;
				}
			}

			if(!comment && (string || (c != '\t' && c != ' '))){
				content += c;
			}
		}

		if(string){
			content += '\n';
		}
	}

	file.close();

	// parse structure
	std::string name = "", value = "";
	std::stack<std::shared_ptr<Node>> nodes;
	Node::TYPE type;

	bool readValue = false, mask = false;
	string = false;
	nodes.push(root);

	for(unsigned int i = 0; i < content.length(); i++){
		c = content.at(i);

		if(c == '\\' && !mask){
			mask = true;

			continue;
		}

		if(!string && c == '"' && !mask){ // string start
			string = true;

			continue;
		}
		else if(string && c == '"' && !mask){ // string end
			string = false;

			continue;
		}

		if(!string){
			if(c == '='){
				readValue = true;

				continue;
			}
			else if(c == ';' || c == ','){
				if(c == ';'){
					if(name.empty()){
						continue;
					}

					nodes.top()->set(name, value, testType(value));

					name = "";
					value = "";
					readValue = false;
				}
				else{
					if(value.empty()){
						continue;
					}

					type = testType(value);

					if(!nodes.top()->value.size() || type == Node::TYPE::STRING || (nodes.top()->type != Node::TYPE::STRING && nodes.top()->type != Node::TYPE::FLOAT)){
						nodes.top()->type = type;
					}

					nodes.top()->value.push_back(value);
					value = "";
				}

				continue;
			}
			else if(c == '{'){
				if(readValue){ // array
					nodes.push(nodes.top()->set(name, "", Node::TYPE::STRING));
				}
				else{ // class
					nodes.push(nodes.top()->set(name, "", Node::TYPE::CLASS));
				}

				name = "";

				continue;
			}
			else if(c == '}'){
				if(readValue){
					if(!value.empty()){
						type = testType(value);

						if(!nodes.top()->value.size() || type == Node::TYPE::STRING || (nodes.top()->type != Node::TYPE::STRING && nodes.top()->type != Node::TYPE::FLOAT)){
							nodes.top()->type = type;
						}

						nodes.top()->value.push_back(value);
					}

					value = "";
					readValue = false;
				}

				if(nodes.size() > 1){
					nodes.pop();
				}

				continue;
			}
			else if(!readValue){
				name += c;
			}
		}

		if(readValue){
			value += c;
		}

		mask = false;
	}

	return true;
}

bool cfgFile::write(const std::string &path, const bool addComment){
	std::ofstream file(path, std::ofstream::out);

	if(!file.good()){
		return false;
	}

	if(addComment){
		file<<"// generated config file"<<std::endl<<std::endl;
	}

	write(file, root);

	return true;
}

std::shared_ptr<cfgFile::Node> cfgFile::getRoot(){
	return root;
}

cfgFile::Node::Node(const std::string &name, const std::string &value, const TYPE type){
	this->name = name;
	this->type = type;

	if(!value.empty()){
		this->value.push_back(value);
	}
}

cfgFile::Node::Node(const std::string &name, const std::string &value):Node(name, value, TYPE::STRING){

}

cfgFile::Node::Node(const std::string &name, const int value):Node(name, std::to_string(value), TYPE::INT){

}

cfgFile::Node::Node(const std::string &name, const float value):Node(name, std::to_string(value), TYPE::FLOAT){

}

cfgFile::Node::Node(const std::string &name):Node(name, "", TYPE::CLASS){

}

std::shared_ptr<cfgFile::Node> cfgFile::Node::set(const std::string &name, const std::string &value, const TYPE type){
	if(type != TYPE::CLASS){
		for(auto n : children){
			if(name == n->getName() && n->getType() != TYPE::CLASS){
				if(n->value.size() == 1){
					n->value[0] = value;
				}
				else if(!value.empty()){
					n->value.push_back(value);
				}

				n->type = type;

				return n;
			}
		}
	}

	auto node = std::shared_ptr<Node>(new Node(name, value, type));
	children.push_back(node);

	return node;
}

std::shared_ptr<cfgFile::Node> cfgFile::Node::set(const std::string &name, const std::string &value){
	return set(name, value, TYPE::STRING);
}

std::shared_ptr<cfgFile::Node> cfgFile::Node::set(const std::string &name, const int value){
	return set(name, std::to_string(value), TYPE::INT);
}

std::shared_ptr<cfgFile::Node> cfgFile::Node::set(const std::string &name, const float value){
	return set(name, std::to_string(value), TYPE::FLOAT);
}

std::shared_ptr<cfgFile::Node> cfgFile::Node::set(const std::string &name){
	return set(name, "", TYPE::CLASS);
}

void cfgFile::Node::set(const std::shared_ptr<Node> node){
	std::string name = node->getName();

	for(auto n : children){
		if(name == n->getName()){
			n->value = node->value;
			n->type = type;
		}
	}

	children.push_back(node);
}

bool cfgFile::Node::remove(const std::string &name){
	for(auto n : children){
		if(name == n->getName()){
			children.remove(n);
			return true;
		}
	}

	return false;
}

void cfgFile::Node::removeAll(const std::string &name){
	while(remove(name)){

	}
}

void cfgFile::Node::remove(const std::shared_ptr<Node> node){
	children.remove(node);
}

cfgFile::Node::TYPE cfgFile::Node::getType(){
	return type;
}

const std::string& cfgFile::Node::getName(){
	return name;
}

std::shared_ptr<cfgFile::Node> cfgFile::Node::get(const std::string &name){
	for(auto n : children){
		if(name == n->getName()/* && n->getType() != TYPE::CLASS*/){
			return n;
		}
	}

	return std::shared_ptr<Node>(new Node(""));
}

void cfgFile::Node::getClasses(const std::string &name, std::list<std::shared_ptr<Node>> &list){
	for(auto n : children){
		if(name == n->getName() && n->getType() == TYPE::CLASS){
			list.push_back(n);
		}
	}
}

const std::list<std::shared_ptr<cfgFile::Node>>& cfgFile::Node::getChildren(){
	return children;
}

std::string cfgFile::Node::toString(const unsigned int i){
	if(i < value.size()){
		return value[i];
	}

	return "";
}

int cfgFile::Node::toInt(const unsigned int i){
	if(i < value.size()){
		try{
			return std::stoi(value[i]);
		}
		catch(...){

		}
	}

	return 0;
}

float cfgFile::Node::toFloat(const unsigned int i){
	if(i < value.size()){
		try{
			return std::stof(value[i]);
		}
		catch(...){

		}
	}

	return 0;
}

};

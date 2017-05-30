#ifndef R_SHELL_H
#define R_SHELL_H

class r_shell {
	public:
		void delete_comments(string &);
		void parse(const string& , vector<string>& );
		void compareCommands(const vector<string>& , vector<string>& );
};

#endif
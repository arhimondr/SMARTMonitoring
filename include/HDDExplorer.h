/*
 * HDDExplorer.h
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#ifndef HDDEXPLORER_H_
#define HDDEXPLORER_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

class HDDExplorer {

private:

	vector<string> availableHDDs;
	bool successfullyDiscovered;

	void discoverHDDs();

public:
	HDDExplorer();
	virtual ~HDDExplorer();
	const vector<string> & getAvailableHDDs() const;
	bool isSuccessfullyDiscovered() const;
};

inline const vector<string> & HDDExplorer::getAvailableHDDs() const{
	return availableHDDs;
}

inline bool HDDExplorer::isSuccessfullyDiscovered() const{
	return successfullyDiscovered;
}

#endif /* HDDEXPLORER_H_ */

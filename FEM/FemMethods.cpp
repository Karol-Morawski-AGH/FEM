#include "FemMethods.h"

std::vector<std::vector<std::string>> readCSV(std::string path, char del)
{
	const char delimeter = del;

	std::ifstream fh(path, std::ifstream::binary);
	if (!fh.is_open())
	{
		std::cout << "ERROR: File " << path << " cannot be opened" << std::endl;
		exit(-1);
	}

	/*Buffered read*/
	fh.seekg(0, fh.end);
	int length = fh.tellg();
	fh.seekg(0, fh.beg);

	char* buffer = new char[length + 1];

	fh.read(buffer, length);
	//NULL terminator
	buffer[length] = '\0';
	fh.close();

	if (!fh)
	{
		std::cout << "ERROR: Only " << fh.gcount() << "could be read in " << path << std::endl;
	}

	std::string fileContent(buffer);
	delete[] buffer;

	/*String parsing and putting into vector*/
	std::vector<std::vector<std::string>> content;
	std::string temp;
	std::vector<std::string> tempVector;


	while (true)
	{
		if (fileContent.find(delimeter) < fileContent.find("\r\n"))
		{
			temp = fileContent.substr(0, fileContent.find(delimeter));
			fileContent = fileContent.substr(fileContent.find(delimeter) + 1);
			tempVector.push_back(temp);
		}
		else if (fileContent.find(delimeter) > fileContent.find("\r\n"))
		{
			temp = fileContent.substr(0, fileContent.find("\r\n"));
			fileContent = fileContent.substr(fileContent.find("\r\n") + 2);
			tempVector.push_back(temp);
			content.push_back(tempVector);
			tempVector.clear();
		}
		else
		{
			temp = fileContent;
			tempVector.push_back(temp);
			content.push_back(tempVector);
			tempVector.clear();
			break;
		}
	}

	return content;
}

std::vector<std::vector<std::string>> readCSV(std::string path)
{
	return readCSV(path, ';');
}

std::vector<std::vector<double>> doubleVector(std::vector<std::vector<std::string>> stringvector)
{
	std::vector<std::vector<double>> casted;

	if (stringvector[0][0].empty())
	{
		std::cout << "ERROR: Vector of strings is empty, cannot cast it to double\n";
		exit(-1);
	}

	for (unsigned int i = 0; i < stringvector.size(); i++)
	{
		std::vector<std::string> tocast = stringvector[i];
		std::vector<double> temp;
		temp.reserve(stringvector.size());
		transform(tocast.begin(), tocast.end(), back_inserter(temp),
			[](std::string const& val) {return stod(val); });

		casted.push_back(temp);
	}
	return casted;
}

// Gaussian Elimination
std::vector<double> gaussianElimination(std::vector<std::vector<double>> A, std::vector<double> B)
{
	std::vector<std::vector<double>> wx;
	std::vector<std::vector<double>> wy;
	std::vector<std::vector<double>> wz;

	//Creates matrix which adds B vector as last column to A matrix
	std::vector<std::vector<double>> matrix = A;

	for (int i = 0; i < A.size(); i++) {
		matrix[i].push_back(B[i]);
	}

	//Eliminatinon
	int n = matrix.size();
	for (int i = 0; i < n - 1; i++)
		for (int k = i + 1; k < n; k++)
		{
			double t = matrix[k][i] / matrix[i][i];
			for (int j = 0; j <= n; j++)
				matrix[k][j] = matrix[k][j] - t * matrix[i][j];
		}

	//Calculating results vector
	std::vector<double> results;

	for (int i = 0; i < n; i++) {
		results.push_back(0);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		results[i] = matrix[i][n];
		for (int j = i + 1; j < n; j++)
			if (j != i)
				results[i] = results[i] - matrix[i][j] * results[j];
		results[i] = results[i] / matrix[i][i];
	}

	return results;
}

void gauss_display(std::vector<double> results) {

	for (int i = 0; i < results.size(); i++) {
		std::cout << "x" << i << ": " << results[i] << std::endl;
	}
}
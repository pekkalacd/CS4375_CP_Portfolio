import math
from typing import (
    List,
    Sequence,
    Union,
    TypeVar,
    Any,
    Dict,
)
Numeric = Union[int,float]


class Metrics:

    @staticmethod
    def accuracy(predicted: List[Numeric], actual: List[Numeric]) -> Numeric:
        return sum(a==p for a,p in zip(actual,predicted))/len(actual)

    @staticmethod
    def recall(predicted: List[Numeric], actual: List[Numeric]) -> Numeric:
        tp=fn=0
        for a,p in zip(actual,predicted):
            if p==1 and a==1:
                tp += 1
            if p==0 and a==1:
                fn += 1
        return tp/(tp+fn)

    @staticmethod
    def precision(predicted: List[Numeric], actual: List[Numeric]) -> Numeric:
        tn=fp=0
        for a,p in zip(actual,predicted):
            if p==0 and a==0:
                tn += 1
            if p==1 and a==0:
                fp += 1
        return tn/(tn+fp)


class Vector:

    @staticmethod
    def add(v1: List[Numeric], v2: List[Numeric]) -> List[Numeric]:
        return list(map(lambda p: p[0]+p[1],zip(v1,v2)))

    @staticmethod
    def sub(v1: List[Numeric], v2: List[Numeric]) -> List[Numeric]:
        return list(map(lambda p: p[0]-p[1],zip(v1,v2)))

    @staticmethod
    def prod(v1: List[Numeric], v2: List[Numeric]) -> List[Numeric]:
        return list(map(lambda p: p[0]*p[1],zip(v1,v2)))

    @staticmethod
    def scale(v1: List[Numeric], s: Numeric) -> List[Numeric]:
        return list(map(lambda v: v*s, v1))


class Algorithm:

    @staticmethod
    def gradient_descent(train_matrix: List[List[Numeric]],
                         target: List[Numeric],
                         weights: List[Numeric],
                         n_iter: int=1000,
                         learning_rate: int=0.001,
                         ):

        for _ in range(n_iter):
            prob_vector = Algorithm.sigmoid(Matrix.dot(train_matrix,weights))
            error = Vector.sub(target,prob_vector)
            weights = Vector.add(Vector.scale(Matrix.dot(Matrix.t(train_matrix),error),learning_rate),weights)
        return weights

    @staticmethod
    def sigmoid(v: List[Numeric]) -> List[Numeric]:
        return list(map(lambda z: 1/(1+math.exp(-1*z)),v))

    @staticmethod
    def predict_probas(v: List[Numeric]) -> List[Numeric]:
        return list(map(lambda lo: (math.exp(lo)/(1+math.exp(lo))),v))

    @staticmethod
    def predict(v: List[Numeric]) -> List[Numeric]:
        return list(map(lambda n: int(n>0.5),v))
    



class File:

    @staticmethod
    def read(filename: str, columns: list=None) -> Union[Exception,Dict[str,List[Numeric]]]:
        data={}
        with open(filename,'r') as file:
            for i,line in enumerate(file.readlines()):
                line=line.strip().split(',')
                if i==0:
                    data = dict.fromkeys(line)
                    for k in data:
                        if columns and k in columns:
                            data[k]=[]
                else:
                    for col,v in zip(data,line):
                        if columns and col in columns:
                            data[col].append(v)
        return data



class Matrix:

    @staticmethod
    def dot(m1: List[List[Numeric]], m2: List[Numeric]) -> List[Numeric]:
        return [(row[0]*m2[0])+(row[1]*m2[1]) for row in m1]

    @staticmethod
    def t(m: List[List[Numeric]]) -> List[Numeric]:
        return list(map(list,zip(*m)))

    @staticmethod
    def cbind(v: List[Numeric], cons: Numeric) -> List[List[Numeric]]:
        return [[a,cons] for a in v]


class Display:

    @staticmethod
    def classification_report(predictions: List[Numeric],
                              actual: List[Numeric],
                              optimal_weights: List[Numeric],
                              ) -> None:
        for i,w in enumerate(optimal_weights):
            print(f"w{i} = {w}",end=" ")

        acc = Metrics.accuracy(predictions,actual)
        sens = Metrics.recall(predictions,actual)
        spec = Metrics.precision(predictions,actual)

        print("")
        print(f"accuracy = {acc}")
        print(f"sensitivity/recall = {sens}")
        print(f"specificity/recall = {spec}")




def main():

    # reading data from titanic.csv
    data: dict = File.read("titanic.csv", columns=["survived","sex"])
    
    # getting 'survived' & 'sex' columns & splitting into train/test
    survived = list(map(int,data["survived"]))
    sex = list(map(lambda v: int(v=='male'),data["sex"]))
    survived_train, survived_test = survived[:800],survived[800:]
    sex_train, sex_test = sex[:800],sex[800:]

    # adjusting sex train and test into matrices w/a column of ones
    sex_train_matrix = Matrix.cbind(sex_train,cons=1)
    sex_test_matrix = Matrix.cbind(sex_test,cons=1)

    # getting optimal weights @ 5000 iterations
    optimal_weights = Algorithm.gradient_descent(sex_train_matrix, survived_train, weights=[1.0,1.0], n_iter=5000, learning_rate=0.001)

    # get log odds vector
    log_odds = Matrix.dot(sex_test_matrix, optimal_weights)

    # get probabilities
    probas = Algorithm.predict_probas(log_odds)

    # get predictions
    predictions = Algorithm.predict(probas)

    # display classification report
    Display.classification_report(predictions, survived_test, optimal_weights)


main()

    

    

    
    


    


dataImoto = read.table("C:/Users/jrey/datapump_imoto.txt", sep = ",")
names(dataImoto) = c("idComputer", "rightDistance","leftDistance","speed","date")
summary(dataImoto)
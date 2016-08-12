X <- matrix(c(0.5,2,1,1,2,3,-1,0,-2,0.5),nrow=2,ncol=5)
lab <- matrix(c(1,1,1,-1,-1),nrow=5,ncol=1)
p <- length(lab)  # nombre de points

# classification  supervisée, détermination des groupes

group1 <- (lab == 1)
group2 <- (lab == -1)
# On insère les variables initiales
w <- c(100,100)
alpha <- rep(1,p)
b <- 3
c0 <- 1e-2
c1 <- 1e-2
continuer <- TRUE
eps <- 1e-3
k<-0
conv <- matrix(nrow= 10000,ncol=2) 
while(continuer)
{
  w_av <- w
  alpha_av <- alpha
  b_av <-b
  
  w[1] <- w_av[1] - c0*(w_av[1]+sum(-alpha_av*lab*X[1,]))
  w[2] <- w_av[2] - c0*(w_av[2]+sum(-alpha_av*lab*X[2,]))
  b <- b_av - c0*sum(-alpha_av*lab)
  alpha <- alpha_av + c1*(1-lab*(X[1,]*w[1] + X[2,]*w[2] + b ))
  for(i in 1:p)
  {
    alpha[i] <- max(alpha[i], 0) 
  }
  print(norm(as.matrix(w-w_av)))
  k <- k+1
  conv[k,1]<- k
  conv[k,2]<- norm(as.matrix(w-w_av))
  
  if(norm(as.matrix(w-w_av)) < eps)
    {   continuer = FALSE  }
}
plot(conv)

xmin <- -5;
ymin <- -5;
xmax <- 5;
ymax <- 5;
plot(X[1,group1],X[2,group1],type='p',lwd=2,asp=1,ylim=c(ymin,ymax),
     xlab="x1",ylab="x2",main="SVM")
points(X[1,group2],X[2,group2],pch=4,lwd=2)

xp <- c(xmin,xmax);
if(w[2] != 0) yp <- (- b - w[1]*xp)/w[2] else xp <- (- b - w[2]*yp)/w[1]
lines(xp,yp,col='red')

if(w[2] != 0) yp <- (1 - b - w[1]*xp)/w[2] else xp <- (1 - b - w[2]*yp)/w[1]
lines(xp,yp,col='blue')
if(w[2] != 0) yp <- (-1 - b - w[1]*xp)/w[2] else xp <- (-1 - b - w[2]*yp)/w[1]
lines(xp,yp,col='blue')
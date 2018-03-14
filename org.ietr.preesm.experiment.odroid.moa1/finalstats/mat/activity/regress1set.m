
%% To be set before calling:
% G: the excitation matrix to inverse
% energy_to_predict: the data to model
%% script returns:
% energy_forward: the predicted energy
% m_cross: the model

%% Pseudo inverse -> maximum likelihood model for norm L2
% Using pseudo inverse, there is no problem of solution existence because
% least square minimization on error is performed

Gt=G.';
GtG=mtimes(Gt,G);
% Applying L2 regularization
Gm1=inv(GtG + eye(size(GtG)))*Gt; % pseudo inverse (least square solution)
m_hat=(Gm1*energy_to_predict)'; % parameter estimation

%% Moore-Penrose pseudo inverse -> works even for low rank G
G_cross=pinv(G);
m_cross=(G_cross*energy_to_predict)';
milli_m_cross = m_cross.*1000;

% Computing error between pseudo-inverses
diff_invG = (Gm1 - G_cross).^2;
error_invG = sum(sum(diff_invG),2)/sum(sum(Gm1),2);

%% Back to forward model
% how well do we match energy data
energy_forward=G*m_cross';

%% Computing global squared error

mse = (sum((energy_forward - energy_to_predict).^2))/size(analyzed_measurements,2);
mse_print = sprintf('%0.10e',mse);
% root-mean-square deviation (RMSD)
rmsd = sqrt(mse);
% coefficient of variation (rmsd in %)
coeff_variation = rmsd/mean(energy_to_predict)*100;

% Chi2 test
%cov_m_hat=inv(GtG)*var_d;


% 95% confidence interval on model based on measurement variance can be
%computed
%confidence_m_hat=1.96*sqrt(diag(cov_m_hat))

% Here variance is considered uniform over d. otherwise, each sigma_i
% must be considered
%Chi2=sum((d-G*m_hat').^2)/var_d

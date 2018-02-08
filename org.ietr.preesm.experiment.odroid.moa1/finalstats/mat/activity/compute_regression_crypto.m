%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Reading data about tokens, quanta and energy and 
%% extracting the architecture model
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc;
clear;
close all;

%% Parameters

% Measured static power (W)
% Careful! Time is always in 10^-1s unit
static_power1 = (35.793392/147)*10;
static_power2 = (32.633362/134)*10;
static_power3 = (42.916309/176)*10;
static_power = (static_power1 + static_power2 + static_power3)/3
%
% setting processor frequencies
freq_A7 = 1400000000;
freq_A15 = 2000000000;
%% We consider 8 cores + 1 communication node = 9 elements
% Tokens and quanta are in alphabetical order:

% A15_Core4,A15_Core5,A15_Core6,A15_Core7,
% A7_Core0,A7_Core1,A7_Core2,A7_Core3,
% shared_mem

%% Characteristics of the input data

prefix = '23-04-2017_1_'
first_measurement = 0; % number of 1st measurement to take into account
nb_measurements = 3666;
% number of energy measurements
nb_experiments = 10;
% repating all measurements n times
nb_parameters = 9; % number of tokens = number of quanta

%% Choosing the analyzed data

% Monocore
analyzed_measurements=[
    64+1,64+2,64+4,64+8,64+16,64+32,64+64,64+128,...
    606+1,606+2,606+4,606+8,606+16,606+32,606+64,606+128,...
    861+1,861+2,861+4,861+8,861+16,861+32,861+64,861+128,...
    1116+1,1116+2,1116+4,1116+8,1116+16,1116+32,1116+64,1116+128,...
    1371+1,1371+2,1371+4,1371+8,1371+16,1371+32,1371+64,1371+128,...
    1626+1,1626+2,1626+4,1626+8,1626+16,1626+32,1626+64,1626+128
    ];


% New stereo w/o broadcast
analyzed_measurements=[64+1:318+1,606+1:1880+1,3411+1:3665+1];
%analyzed_measurements=[64+1:318+1,606+1:1880+1];

%analyzed_measurements=[3411+1:3665+1];

%analyzed_measurements=[64+1:318+1];

%analyzed_measurements=[606+1:606+255+1];

%analyzed_measurements=[64+1:64+14+1];

%analyzed_measurements=[64+1:64+15+14+1];

%analyzed_measurements=[64+1:64+60];

analyzed_experiments=[1,10];

% We take lambda = 1 for the moment

%% Retrieving table of tokens
load(strcat(prefix,'tokens.mat')); % tokens
tokens = tokens(first_measurement+1:first_measurement+nb_measurements,:);

% Taking into account the number of iterations
% The energy is per iteration
% The 64 first experiments (0-63) are over 1000 iterations
tokens(1:63+1,:) = tokens(1:63+1,:).*1000;

% The next experiments are over 10 iterations 
tokens(64+1:nb_measurements,:) = tokens(64+1:nb_measurements,:).*10;

% Experiment 5 is over 100 iterations
tokens(1371+1:1625+1,:) = tokens(1371+1:1625+1,:).*10;

% Experiment crypto is over 160 iterations
tokens(3411+1:3665+1,:) = tokens(3411+1:3665+1,:).*16;

% Keeping only analyzed elements
tokens = keeprows(tokens,analyzed_measurements);

%% Retrieving table of quanta (in ps of execution on a Cortex_A7)
load(strcat(prefix,'quanta.mat')); % quanta in Mcycles
quanta = quanta(first_measurement+1:first_measurement+nb_measurements,:);

% Taking into account the number of iterations
% The energy is per iteration
% The 64 first experiments (0-63) are over 1000 iterations
quanta(1:63+1,:) = quanta(1:63+1,:).*1000;

% The next experiments are over 10 iterations 
quanta(64+1:nb_measurements,:) = quanta(64+1:nb_measurements,:).*10;

% Experiment 5 is over 100 iterations
quanta(1371+1:1625+1,:) = quanta(1371+1:1625+1,:).*10;

% Experiment crypto is over 160 iterations
quanta(3411+1:3665+1,:) = quanta(3411+1:3665+1,:).*16;

% Keeping only analyzed elements
quanta = keeprows(quanta,analyzed_measurements);

% quanta_prime is the number of quanta per token
tempsparse = sparse(zeros(size(quanta)));
linIndices = find(quanta);
tempsparse(linIndices) = quanta(linIndices) ./ tokens(linIndices);
quanta_prime=full(tempsparse);


% %% Retrieving table of custom quanta (in uJ of execution on a Cortex_A7/A15)
% load(strcat(prefix,'custom_quanta.mat')); % quanta in Mcycles
% q_custom = q_custom(first_measurement+1:first_measurement+nb_measurements,:);
% 
% % Taking into account the number of iterations
% % The energy is per iteration
% % The 64 first experiments (0-63) are over 1000 iterations
% q_custom(1:63+1,:) = q_custom(1:63+1,:).*1000;
% 
% % The next experiments are over 10 iterations 
% q_custom(64+1:nb_measurements,:) = q_custom(64+1:nb_measurements,:).*10;
% 
% % Experiment 5 is over 100 iterations 
% q_custom(1371+1:1625+1,:) = q_custom(1371+1:1625+1,:).*10;
% 
% % Keeping only analyzed elements
% q_custom = keeprows(q_custom,analyzed_measurements);
% 
% % Testing effect of errors in #quanta 
% %r1 = rand(size(q_custom))
% %q_custom = q_custom.* r1 *10
% 
% % quanta_prime is the number of quanta per token
% tempsparse = sparse(zeros(size(q_custom)));
% linIndices = find(q_custom);
% tempsparse(linIndices) = q_custom(linIndices) ./ tokens(linIndices);
% q_custom_prime = full(tempsparse);

%%%%%%%%%%%
one_val=0;
if(one_val==1)
%%%%%%%%%%%

%% 3CN section: repeated simulation with one CN per cluster + shared mem

%% Retrieving table of tokens 3CN
load(strcat(prefix,'tokens_3CN.mat')); % tokens
tokens_3CN = tokens_3CN(first_measurement+1:first_measurement+nb_measurements,:);

% Taking into account the number of iterations
% The energy is per iteration
% The 64 first experiments (0-63) are over 1000 iterations
tokens_3CN(1:63+1,:) = tokens_3CN(1:63+1,:).*1000;

% The next experiments are over 10 iterations 
tokens_3CN(64+1:nb_measurements,:) = tokens_3CN(64+1:nb_measurements,:).*10;

% Experiment 5 is over 100 iterations
tokens_3CN(1371+1:1625+1,:) = tokens_3CN(1371+1:1625+1,:).*10;

% Keeping only analyzed elements
tokens_3CN = keeprows(tokens_3CN,analyzed_measurements);

%% Retrieving quanta 3CN
load(strcat(prefix,'quanta_3CN.mat')); % quanta in Mcycles
quanta_3CN = quanta_3CN(first_measurement+1:first_measurement+nb_measurements,:);

% Taking into account the number of iterations
% The energy is per iteration
% The 64 first experiments (0-63) are over 1000 iterations
quanta_3CN(1:63+1,:) = quanta_3CN(1:63+1,:).*1000;

% The next experiments are over 10 iterations 
quanta_3CN(64+1:nb_measurements,:) = quanta_3CN(64+1:nb_measurements,:).*10;

% Experiment 5 is over 100 iterations
quanta_3CN(1371+1:1625+1,:) = quanta_3CN(1371+1:1625+1,:).*10;

% Keeping only analyzed elements
quanta_3CN = keeprows(quanta_3CN,analyzed_measurements);

% quanta_prime is the number of quanta per token
tempsparse = sparse(zeros(size(quanta_3CN)));
linIndices = find(quanta_3CN);
tempsparse(linIndices) = quanta_3CN(linIndices) ./ tokens_3CN(linIndices);
quanta_3CN_prime=full(tempsparse);


%% Retrieving table of custom quanta 3CN
load(strcat(prefix,'custom_quanta_3CN.mat')); % quanta in Mcycles
q_custom_3CN = q_custom_3CN(first_measurement+1:first_measurement+nb_measurements,:);

% Taking into account the number of iterations
% The energy is per iteration
% The 64 first experiments (0-63) are over 1000 iterations
q_custom_3CN(1:63+1,:) = q_custom_3CN(1:63+1,:).*1000;

% The next experiments are over 10 iterations 
q_custom_3CN(64+1:nb_measurements,:) = q_custom_3CN(64+1:nb_measurements,:).*10;

% Experiment 5 is over 100 iterations 
q_custom_3CN(1371+1:1625+1,:) = q_custom_3CN(1371+1:1625+1,:).*10;

% Keeping only analyzed elements
q_custom_3CN = keeprows(q_custom_3CN,analyzed_measurements);

% quanta_prime is the number of quanta per token
tempsparse = sparse(zeros(size(q_custom_3CN)));
linIndices = find(q_custom_3CN);
tempsparse(linIndices) = q_custom_3CN(linIndices) ./ tokens_3CN(linIndices);
q_custom_3CN_prime = full(tempsparse);

%%%%%%%%%%%   
end
%%%%%%%%%%%

%% Retrieving vector of time (to compute static energy)
load(strcat(prefix,'time.mat')); % time in seconds
time = time(first_measurement+1:first_measurement+nb_measurements,:);

% Keeping only analyzed elements
time = keeprows(time,analyzed_measurements);

%% Retrieving vector of energy
load(strcat(prefix,'energy_raw.mat')); % energy in Joule
energy_raw = energy_raw(first_measurement+1:first_measurement+nb_measurements,:);

% Keeping only analyzed elements
energy_raw = keeprows(energy_raw,analyzed_measurements);

% Removing the static energy from measurements
energy = energy_raw - (time.*static_power);


%% Predicting with number of quanta: step 1
%% Predicting error with #quanta

disp( sprintf( 'Step %d!', 1 ) )
% Averaging enenergy over the different measurements
energy_to_predict = median(energy,2);
energy_to_predict_step1 = energy_to_predict;

%% Building matrix G of system excitation

scale_quanta = mean2(quanta); % Scaling powers for readability
scale_tokens = mean2(tokens);

GQ2 = [quanta,(quanta.^2)./scale_quanta];
GT2 = [tokens,(tokens.^2)./scale_tokens];

%G = [q_custom_3CN,tokens(:,1:8).^2./mean2(tokens(:,1:8))];
%G = [tokens_3CN,q_custom_3CN];
G = [tokens,quanta];

%% Calling regression to obtain m_cross 
regress1set;

%% Fixing m to the average power per core
%% Taking minimum to have positive correction
%milli_m_cross_corrected = [1.48,1.48,1.48,1.48,0.24,0.24,0.24,0.24,0];
milli_m_cross
%milli_m_cross_corrected = [1.24,1.24,1.24,1.24,2.2,2.2,2.2,2.2];

%m_cross_corrected = milli_m_cross_corrected./1000;
%!!!!! Forcing energy forward !!!!!
%energy_forward=G*m_cross_corrected';

energy_forward_step1 = energy_forward;

%% Correcting the prediction with #tokens: step 2
% 

% disp( sprintf( 'Step %d!', 2 ) )
% energy_to_predict = energy_to_predict - energy_forward;
% 
% energy_to_predict = energy_to_predict+2;
% energy_to_predict_step2 = energy_to_predict;

%% Building matrix G of system excitation
% 
% G = [tokens(:,1:8).^2./mean2(tokens(:,1:8))];
% 
% regress1set;
% milli_m_cross

%milli_m_cross_corrected = [0,0,0,0,0,0,0,0];
%m_cross_corrected = milli_m_cross_corrected./1000;

%!!!!! Forcing energy forward !!!!!
%energy_forward=G*m_cross_corrected';
% 
% energy_to_predict = energy_to_predict-2;
% energy_forward_step2 = energy_forward-2;

%% Correcting the prediction with communications of 3CN: step 3
% 

% disp( sprintf( 'Step %d!', 3 ) )
% energy_to_predict = energy_to_predict - energy_forward;
% energy_to_predict_step3 = energy_to_predict;


%% Building matrix G of system excitation

%G = [tokens_3CN(:,9:11),quanta_3CN(:,9:11),tokens_3CN(:,9:11).^2,quanta_3CN(:,9:11).^2] % Communication tokens
% G = [tokens_3CN(:,9:11)]; % Communication tokens
% 
% regress1set;
% milli_m_cross
% 
% energy_forward_step3 = energy_forward;

%% Analyzing energy variations

% Evaluating energy standard deviation effect
stddev_energy = std(energy,0,2);
mean_energy = mean2(energy);
mean_stddev_energy = mean(stddev_energy);
coefficient_of_variation = mean_stddev_energy/mean_energy;
min(stddev_energy);
max(stddev_energy);
%coefficient_of_variation = stddev_energy ./ energy_to_predict * 100

%% Analyzing effects of tokens and quanta independently

%m_cross_quanta = m_cross
%m_cross_quanta(1:11)=zeros(1,11)

%energy_quanta = G*m_cross_quanta'

%% Analyzing prediction error in configuration 4

%mse = (sum((energy_forward(766:766+254,:) - energy_to_predict(766:766+254,:)).^2))/255;
%mse_print = sprintf('%0.10e',mse);
% root-mean-square deviation (RMSD)
%rmsd = sqrt(mse)
% coefficient of variation (rmsd in %)
%coeff_variation = rmsd/mean(energy_to_predict(766:766+254,:))*100

%% Plotting results

%%%%%%%%%%%
one_val=0;
if(one_val==1)
%%%%%%%%%%%


    dx=[0:1:nb_measurements-1];
    h=figure

    % Raw figure of energy with boxplot

    boxplot(energy','symbol','');

    set(h,'PaperPosition', [1 1 11 5]);
    set(h,'papersize', [15 10]);
    print -painters -depsc -r2000 energy_box.eps

%%%%%%%%%%%   
end
%%%%%%%%%%%


%%%%%%%%%%%
one_val=1;
if(one_val==0)
%%%%%%%%%%%
    % Figure of prediction
    h=figure;
    markers = {'r+','go','b*','r.','gx','bs','r^','gv','b>','r<'};

    hold on
    plot(energy_forward_step1,'r-');
    plot(energy_to_predict_step1(:,1),'b.');
    plot(energy_quanta,'r:');
    hold off

    set(h,'papersize', [30 15]);
    set(h,'PaperPosition', [0 0 25 5]);
    print -painters -depsc -r1400 energy_model.eps

%%%%%%%%%%%   
end
%%%%%%%%%%%

%% Computing the learning curve

% randomly sampling training set and validation set
% Full data set is 1530
% Training set is up to 80%, i.e . 1224
% Validation set is fixed to 20%, i.e. 306

rng('shuffle')

fullsize=1530;
trainingsize=1224;
validsize=fullsize-trainingsize;
cryptosize=255;

trainingindex = datasample(1:fullsize,trainingsize,'Replace',false);
trainingset = energy_forward_step1(trainingindex);
%plot(trainingset);

validindex = setdiff(1:fullsize,trainingindex);
validset = energy_forward_step1(validindex);

cryptoindex=1531:1:1785;
cryptoset=energy_forward_step1(cryptoindex);

validindex = cryptoindex
validset = cryptoset

%plot(validset);


% %% RMSD Figure 
% 
 G_save=G;
 energy_to_predict_save=energy_to_predict;
% 
% % Iterating over the size of the training set to extract rmsd and
% % rmsd_valid
% for ts =1:trainingsize
%     G_training=G_save(trainingindex(1:ts),:);
%     energy_to_predict_training=energy_to_predict_save(trainingindex(1:ts));
%     
%     G=G_training;
%     energy_to_predict=energy_to_predict_training;
%     % Needs G and energy_to_predict
%     regress1set;
% 
%     % Computing RMSD for the validation set
%     energy_to_predict_valid=energy_to_predict_save(validindex);
%     G_valid=G_save(validindex,:);
%     energy_forward_valid = G_valid*m_cross';
%     mse = (sum((energy_forward_valid - energy_to_predict_valid).^2))/validsize;
%     % root-mean-square deviation (RMSD)
%     rmsd_tab(ts) = rmsd; % Computed in regress1set
%     rmsd_valid_tab(ts) = sqrt(mse);
%     rmsd;
%     rmsd_valid = sqrt(mse);
%     
% %     hold on
% %     plot(energy_forward_valid,'r-');
% %     plot(energy_to_predict_valid,'b.');
% %     hold off
% end

% Training RMSD, rising progressively, Validation RMSD, decreasing
%plot(1:trainingsize,rmsd_tab,'r-',1:trainingsize,rmsd_valid_tab,'b--'); 
%axis([1 trainingsize 0 5]);
%legend('Training RMSD error','Validation RMSD error');
%xlabel('Size in samples of the LSLA model training set');
%ylabel('RMSD error (in Joules) between prediction and measure');

%print -painters -depsc -r2000 validation.eps

%% Energy 1 figure on training set

ts=trainingsize
sorted_index=sort(trainingindex(1:ts));

energy_training=energy(sorted_index,:);

% h=figure
% boxplot(energy_training','symbol','');
% set(h,'PaperPosition', [1 1 11 5]);
% set(h,'papersize', [15 10]);
% print -painters -depsc -r2000 energy1.eps

%% Energy 2 figure on crypto set

ts=trainingsize

G_training=G_save(trainingindex(1:ts),:);
energy_to_predict_training=energy_to_predict_save(trainingindex(1:ts));

G=G_training;
energy_to_predict=energy_to_predict_training;
% Needs G and energy_to_predict
regress1set;

% Computing RMSD for the validation set
energy_to_predict_valid=energy_to_predict_save(validindex);
G_valid=G_save(validindex,:);
energy_forward_valid = G_valid*m_cross';
mse = (sum((energy_forward_valid - energy_to_predict_valid).^2))/validsize;

h=figure;
markers = {'r+','go','b*','r.','gx','bs','r^','gv','b>','r<'};

hold on
plot(energy_forward_valid,'r-');
plot(energy_to_predict_valid,'b.');
hold off

set(h,'papersize', [30 15]);
set(h,'PaperPosition', [0 0 25 5]);
print -painters -depsc -r1400 energy2.eps

set(h,'PaperPosition', [0 0 6 3]);
    set(h,'papersize', [5 3]);

%% Analyzing fidelity
% corresponds to the probability that the estimator "orders" the results similarly to reality
% See bamb2000x1.pdf for definition

fij=zeros(validsize,validsize);

for i =1:size(energy_forward_valid,1)
    for j =1:size(energy_forward_valid,1)
        temp1 = (energy_forward_valid(i,1)-energy_forward_valid(j,1));
        temp2 = (energy_to_predict_valid(i,1)-energy_to_predict_valid(j,1));
        if sign(temp1) == sign(temp2)
            fij(i,j) = 1;
        end
    end
end

%%taking upper triangle w/o diagonal ans summing
fidelity = 2/(validsize*(validsize-1))*sum(sum(triu(fij,1)),2)
size(fij(1,:))

sorted_energy_valid = sortrows([energy_forward_valid,energy_to_predict_valid],2);
sorted_energy_forward_valid = sorted_energy_valid(:,1);
sorted_energy_to_predict_valid = sorted_energy_valid(:,2);

% Figure of sorted energy
h=figure;
plot(sorted_energy_to_predict_valid(:,1),'b.');
hold on;
plot(sorted_energy_forward_valid(:,1),'r-');
hold off;
title('Prediction in order') ;
xlabel('experiment number') ;
ylabel('energy');
set(h,'PaperPosition', [0 0 6 3]);
set(h,'papersize', [5 3]);
print -painters -depsc -r2000 fidelity.eps;

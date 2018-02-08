%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Reading data about tokens and quanta, with 3 communication nodes
%% and storing them in a Matlab file
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc;
close all;

%% Parameters

% setting processor frequencies
freq_A7 = 1400000000;
freq_A15 = 2000000000;
%% We consider 8 cores + 1 communication node = 9 elements
% Tokens and quanta are in alphabetical order:

% A15_Core4,A15_Core5,A15_Core6,A15_Core7,
% A7_Core0,A7_Core1,A7_Core2,A7_Core3,
% shared_mem

%% Indexes as read in data

nb_measurements = 255;

% directory = '../../../../MoAExperimentalResults/Scenario1_3CN_22-08-2016/'
% first_measurement = 64; % number of 1st measurement to take into account
% scenario_index = 1881;

% directory = '../../../../MoAExperimentalResults/Scenario2_3CN_22-08-2016/'
% first_measurement = 606; % number of 1st measurement to take into account
% scenario_index = 1881+255;

% directory = '../../../../MoAExperimentalResults/Scenario3_3CN_22-08-2016/'
% first_measurement = 861; % number of 1st measurement to take into account
% scenario_index = 1881+2*255;

% directory = '../../../../MoAExperimentalResults/Scenario4_3CN_22-08-2016/'
% first_measurement = 1116; % number of 1st measurement to take into account
% scenario_index = 1881+3*255;

% directory = '../../../../MoAExperimentalResults/Scenario5_3CN_23-08-2016/'
% first_measurement = 1371; % number of 1st measurement to take into account
% scenario_index = 1881+4*255;

% directory = '../../../../MoAExperimentalResults/Scenario6_3CN_23-08-2016/'
% first_measurement = 1626; % number of 1st measurement to take into account
% scenario_index = 1881+5*255;

% number of energy measurements
nb_experiments = 10;
nb_parameters = 11;

in_prefix = '23-08-2016_1_'
out_prefix = '23-08-2016_1_'

%% Retrieving table of tokens
% tokens are verified to be identical for all experiments
if(first_measurement == 0)
    tokens_3CN = zeros(nb_measurements, nb_parameters);
    
else    
    % If it exists, tokens.mat is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'tokens_3CN.mat'), 'file') == 2)
        load(strcat(in_prefix,'tokens_3CN.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(tokens_3CN,1)<first_measurement)
            tokens_3CN = [tokens_3CN;zeros(first_measurement-size(tokens_3CN,1), nb_parameters)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        tokens_3CN = zeros(first_measurement, nb_parameters);
    end
    
    % Appending space for new tokens
    if(size(tokens_3CN,1)<first_measurement+nb_measurements)
        tokens_3CN = [tokens_3CN;zeros(first_measurement+nb_measurements-size(tokens_3CN,1), nb_parameters)];
    end
end

sci = scenario_index;
for i=first_measurement:first_measurement+nb_measurements-1
    % Getting file name for the correct csv file
    csvfile=sprintf('%s0_I0_tokens_%d.csv',directory,sci);
    token_row = csvread(csvfile);
    tokens_3CN(1+i,:) = token_row;
    sci = sci+1;
end

size_tokens = size(tokens_3CN)
save(strcat(out_prefix,'tokens_3CN.mat'),'tokens_3CN')

%% Retrieving table of quanta (in ps of execution on a Cortex_A7)
% quanta are verified to be identical for all experiments
if(first_measurement == 0)
    quanta_3CN = zeros(nb_measurements, nb_parameters); 
else    
    % If it exists, the file is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'quanta_3CN.mat'), 'file') == 2)
        load(strcat(in_prefix,'quanta_3CN.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(quanta_3CN,1)<first_measurement)
            quanta_3CN = [quanta_3CN;zeros(first_measurement-size(quanta_3CN,1), nb_parameters)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        quanta_3CN = zeros(first_measurement, nb_parameters);
    end
    
    % Appending space for new data
    if(size(quanta_3CN,1)<first_measurement+nb_measurements)
        quanta_3CN = [quanta_3CN;zeros(first_measurement+nb_measurements-size(quanta_3CN,1), nb_parameters)];
    end
end

% computation quanta are expressed in ps of execution
% communication quanta are expressed in MBytes

sci = scenario_index;
for i=first_measurement:first_measurement+nb_measurements-1
    % Getting file name for the correct csv file
    csvfile=sprintf('%s0_I0_quanta_%d.csv',directory,sci);
    quanta_row = csvread(csvfile);
    
    % Quanta in ps
    quanta_row(:,1:8) = quanta_row(:,1:8) ./10^9; %converting into ms
    quanta_row(:,9:11) = quanta_row(:,9:11) ./10^6; %converting into MB

    quanta_3CN(1+i,:) = quanta_row;
    sci = sci+1;
end

size_quanta = size(quanta_3CN)
save(strcat(out_prefix,'quanta_3CN.mat'),'quanta_3CN')


%% Retrieving table of custom quanta (J of execution on a Cortex_A7/A15)
% quanta are verified to be identical for all experiments
if(first_measurement == 0)
    q_custom_3CN = zeros(nb_measurements, nb_parameters); 
else    
    % If it exists, the file is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'custom_quanta_3CN.mat'), 'file') == 2)
        load(strcat(in_prefix,'custom_quanta_3CN.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(q_custom_3CN,1)<first_measurement)
            q_custom_3CN = [q_custom_3CN;zeros(first_measurement-size(q_custom_3CN,1), nb_parameters)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        q_custom_3CN = zeros(first_measurement, nb_parameters);
    end
    
    % Appending space for new data
    if(size(q_custom_3CN,1)<first_measurement+nb_measurements)
        q_custom_3CN = [q_custom_3CN;zeros(first_measurement+nb_measurements-size(q_custom_3CN,1), nb_parameters)];
    end
end

% computation quanta are expressed in mJ of execution over one A7/A15 core
% communication quanta are expressed in MBytes

% Scaling down big quanta (results in Joules)

sci = scenario_index;
for i=first_measurement:first_measurement+nb_measurements-1
    % Getting file name for the correct csv file
    csvfile=sprintf('%s0_I0_custom_quanta_%d.csv',directory,sci);
    quanta_row = csvread(csvfile);
    
    % Transforming quanta from pJ of execution to mJ
    quanta_row(:,1:8) = quanta_row(:,1:8) ./10^9; %converting into mJ
    quanta_row(:,9:11) = quanta_row(:,9:11) ./10^6; %converting into MB

    q_custom_3CN(1+i,:) = quanta_row;
    sci = sci+1;
end

size_quanta = size(q_custom_3CN)
save(strcat(out_prefix,'custom_quanta_3CN.mat'),'q_custom_3CN')

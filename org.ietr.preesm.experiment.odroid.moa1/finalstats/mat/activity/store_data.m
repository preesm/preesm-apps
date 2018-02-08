%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Reading data about tokens, quanta, power, time and energy 
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

% directory = '../../../../MoAExperimentalResults/Scenario1_N10_14-08-2016/'
% first_measurement = 64; % number of 1st measurement to take into account

% directory = '../../../../MoAExperimentalResults/Scenario2_N10_14-08-2016/'
% first_measurement = 606; % number of 1st measurement to take into account

% directory = '../../../../MoAExperimentalResults/Scenario3_N10_14-08-2016/'
% first_measurement = 861; % number of 1st measurement to take into account

% directory = '../../../../MoAExperimentalResults/Scenario4_N10_18-08-2016/'
% first_measurement = 1116; % number of 1st measurement to take into account

% directory = '../../../../MoAExperimentalResults/Scenario5_N100_21-08-2016/'
% first_measurement = 1371; % number of 1st measurement to take into account

%directory = '../../../../MoAExperimentalResults/Scenario6_N10_20-08-2016/'
%first_measurement = 1626; % number of 1st measurement to take into account
 
directory = './22-04-2017/'
first_measurement = 3411; % number of 1st measurement to take into account

% number of energy measurements
nb_experiments = 10;
nb_parameters = 9;

in_prefix = '23-08-2016_1_'
out_prefix = '23-04-2017_1_'

%% Retrieving table of tokens
% tokens are verified to be identical for all experiments
if(first_measurement == 0)
    tokens = zeros(nb_measurements, nb_parameters);
    
else    
    % If it exists, tokens.mat is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'tokens.mat'), 'file') == 2)
        load(strcat(in_prefix,'tokens.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(tokens,1)<first_measurement)
            tokens = [tokens;zeros(first_measurement-size(tokens,1), nb_parameters)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        tokens = zeros(first_measurement, nb_parameters);
    end
    
    % Appending space for new tokens
    if(size(tokens,1)<first_measurement+nb_measurements)
        tokens = [tokens;zeros(first_measurement+nb_measurements-size(tokens,1), nb_parameters)];
    end
end

for i=first_measurement:first_measurement+nb_measurements-1
    % Getting file name for the correct csv file
    csvfile=sprintf('%s0_I0_tokens_%d.csv',directory,i);
    token_row = csvread(csvfile);
    tokens(1+i,:) = token_row;
end

size_tokens = size(tokens)
save(strcat(out_prefix,'tokens.mat'),'tokens')

%% Retrieving table of quanta
% quanta are verified to be identical for all experiments
if(first_measurement == 0)
    quanta = zeros(nb_measurements, nb_parameters); 
else    
    % If it exists, the file is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'quanta.mat'), 'file') == 2)
        load(strcat(in_prefix,'quanta.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(quanta,1)<first_measurement)
            quanta = [quanta;zeros(first_measurement-size(quanta,1), nb_parameters)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        quanta = zeros(first_measurement, nb_parameters);
    end
    
    % Appending space for new data
    if(size(quanta,1)<first_measurement+nb_measurements)
        quanta = [quanta;zeros(first_measurement+nb_measurements-size(quanta,1), nb_parameters)];
    end
end

% computation quanta are expressed in ms
% communication quanta are expressed in MBytes

for i=first_measurement:first_measurement+nb_measurements-1
    % Getting file name for the correct csv file
    csvfile=sprintf('%s0_I0_quanta_%d.csv',directory,i);
    quanta_row = csvread(csvfile);
    
    % Transforming quanta
    quanta_row(:,1:8) = quanta_row(:,1:8) ./10^9; %converting into ms
    quanta_row(:,9) = quanta_row(:,9) ./10^6; %converting into MB
    
    quanta(1+i,:) = quanta_row;
end

size_quanta = size(quanta)
save(strcat(out_prefix,'quanta.mat'),'quanta')


% %% Retrieving table of custom quanta (mJ of execution on a Cortex_A7/A15)
% % quanta are verified to be identical for all experiments
% if(first_measurement == 0)
%     q_custom = zeros(nb_measurements, nb_parameters); 
% else    
%     % If it exists, the file is supposed to contain data starting from
%     % index 0
%     if(exist(strcat(in_prefix,'custom_quanta.mat'), 'file') == 2)
%         load(strcat(in_prefix,'custom_quanta.mat')); % load existing data
%         
%         % Insert zeros if necessary between retrieved values and
%         % the 1st new measurement (if difference in index
%         if(size(q_custom,1)<first_measurement)
%             q_custom = [q_custom;zeros(first_measurement-size(q_custom,1), nb_parameters)];
%         end
%         
%     else
%         % If the input file does not exist, put 0 in values before the 1st
%         % retrieved ones
%         q_custom = zeros(first_measurement, nb_parameters);
%     end
%     
%     % Appending space for new data
%     if(size(q_custom,1)<first_measurement+nb_measurements)
%         q_custom = [q_custom;zeros(first_measurement+nb_measurements-size(q_custom,1), nb_parameters)];
%     end
% end

% computation quanta are expressed in mJ of execution over one A7/A15 core
% communication quanta are expressed in MBytes

% Scaling down big quanta (results in Joules)

% for i=first_measurement:first_measurement+nb_measurements-1
%     % Getting file name for the correct csv file
%     csvfile=sprintf('%s0_I0_custom_quanta_%d.csv',directory,i);
%     quanta_row = csvread(csvfile);
%     
%     % Transforming quanta from pJ of execution to mJ
%     quanta_row(:,1:8) = quanta_row(:,1:8) ./10^9; %converting into mJ
%     quanta_row(:,9) = quanta_row(:,9) ./10^6; %converting into MB
% 
%     q_custom(1+i,:) = quanta_row;
% end
% 
% size_quanta = size(q_custom)
% save(strcat(out_prefix,'custom_quanta.mat'),'q_custom')

%% Retrieving vector of time (to compute static energy)

if(first_measurement == 0)
    time = zeros(nb_measurements, nb_experiments); 
else    
    % If it exists, the file is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'time.mat'), 'file') == 2)
        load(strcat(in_prefix,'time.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(time,1)<first_measurement)
            time = [time;zeros(first_measurement-size(time,1), nb_experiments)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        time = zeros(first_measurement, nb_experiments);
    end
    
    % Appending space for new data
    if(size(time,1)<first_measurement+nb_measurements)
        time = [time;zeros(first_measurement+nb_measurements-size(time,1), nb_experiments)];
    end
end

for j=0:nb_experiments-1
    for i=first_measurement:first_measurement+nb_measurements-1
        % Getting file name for the correct csv file
        csvfile=sprintf('%s0_I%d_time_%d.csv',directory,j,i);
        if(exist(csvfile,'file'))
            time_row = csvread(csvfile);
            
            time_row = (time_row-1) ./ 10; % converting time into seconds and 
            % forgetting last empty line

            time(1+i,j+1) = time_row;
        else
            disp(strcat('file not found ', csvfile))
            time_row = 0;
            time(1+i,j+1) = time_row;
        end
    end
end

size_time = size(time)
save(strcat(out_prefix,'time.mat'),'time')

%% Retrieving table of power (in W sampled at 10 Hz)
%% Powers of memory, A7 and A15 are retrieved independently

% Not ready for disjoint data retrieval

% if(first_measurement == 0)
%     power = zeros(nb_measurements, nb_experiments,max(max(time*10)),3);
% else
%     load(strcat(in_prefix,'power.mat')); % load existing data
%     s = size(power);
%     w = max(max(max(time*10)), s(3));% width of the new matrix
%     if(s(3)<w)
%         cat(3,power,zeros(nb_measurements, nb_experiments,w-s(3),3));
%     end
%     cat(1,power,zeros(nb_measurements, nb_experiments,w,3));
% end
% % computation quanta are expressed in ps of execution over one A7 core
% % communication quanta are expressed in Bytes
% 
% for j=0:nb_experiments-1
%     for i=first_measurement:first_measurement+nb_measurements-1
%         csvfile=sprintf('%s0_I%d_power_%d.csv',directory,j,i);
%         try
%             power_raw_expe = csvread(csvfile);
%         catch err
%             strcat('empty file ', csvfile)
%         end
%         for k=1:(time(i+1,j+1)*10)
%             % Getting file name for the correct csv file
%             power(1+i,j+1,k,:) = power_raw_expe(k,:);
%         end
% 
%     end
% end
% 
% size_power = size(power)
% save(strcat(out_prefix,'power.mat'),'power')

%% Retrieving vector of energy

if(first_measurement == 0)
    energy_raw = zeros(nb_measurements, nb_experiments); 
else    
    % If it exists, the file is supposed to contain data starting from
    % index 0
    if(exist(strcat(in_prefix,'energy_raw.mat'), 'file') == 2)
        load(strcat(in_prefix,'energy_raw.mat')); % load existing data
        
        % Insert zeros if necessary between retrieved values and
        % the 1st new measurement (if difference in index
        if(size(energy_raw,1)<first_measurement)
            energy_raw = [energy_raw;zeros(first_measurement-size(energy_raw,1), nb_experiments)];
        end
        
    else
        % If the input file does not exist, put 0 in values before the 1st
        % retrieved ones
        energy_raw = zeros(first_measurement, nb_experiments);
    end
    
    % Appending space for new data
    if(size(energy_raw,1)<first_measurement+nb_measurements)
        energy_raw = [energy_raw;zeros(first_measurement+nb_measurements-size(energy_raw,1), nb_experiments)];
    end
end

for j=0:nb_experiments-1
    for i=first_measurement:first_measurement+nb_measurements-1
        % Getting file name for the correct csv file
        csvfile=sprintf('%s0_I%d_energy_%d.csv',directory,j,i);
        if(exist(csvfile,'file'))
            energy_raw_row = csvread(csvfile);
            energy_raw(1+i,j+1) = energy_raw_row;
        else
            disp(strcat('file not found ', csvfile))
            energy_raw = 0;
            energy_raw(1+i,j+1) = energy_raw_row;
        end
    end
end

% energy_raw is in J and contains static power.
energy_raw;

size_energy_raw = size(energy_raw)
save(strcat(out_prefix,'energy_raw.mat'),'energy_raw')

figure

%for i=1:1
%  subplot(1,1,1);
%  plot(dx,energy(:,i),'r',dx,energy_forward(:,i),'b--');
%end

markers = {'r+','go','b*','r.','gx','bs','r^','gv','b>','r<'};

dx=[0:1:first_measurement+nb_measurements-1];

hold on % Putting together all measurements
for i=1:nb_experiments
  plot(dx,energy_raw(:,i),markers{mod(i,numel(markers))+1});
end
hold off % Back to normal plot

title('Energy experiments') 
xlabel('experiment number') 
ylabel('energy')       
%legend('nuage 1','nuage 2');

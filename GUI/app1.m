classdef app1 < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure                       matlab.ui.Figure
        GridLayout                     matlab.ui.container.GridLayout
        LeftPanel                      matlab.ui.container.Panel
        TabGroup                       matlab.ui.container.TabGroup
        AlignmentTab                   matlab.ui.container.Tab
        FilterSetupPanel               matlab.ui.container.Panel
        SaveCalibrationButton          matlab.ui.control.Button
        HomePositionButton_3           matlab.ui.control.Button
        MoveButton                     matlab.ui.control.Button
        MoveMotortostepNoEditField     matlab.ui.control.NumericEditField
        MoveMotortostepNoEditFieldLabel  matlab.ui.control.Label
        CurrentWavelengthEditField_3   matlab.ui.control.NumericEditField
        CurrentWavelengthEditField_3Label  matlab.ui.control.Label
        CurrentPositionEditField_4     matlab.ui.control.NumericEditField
        CurrentPositionEditField_4Label  matlab.ui.control.Label
        UpdateCurrentWavelengthButton_3  matlab.ui.control.Button
        UpdateCurrentPositionButton_3  matlab.ui.control.Button
        CurrentPositionEditField_3     matlab.ui.control.NumericEditField
        CurrentPositionEditField_3Label  matlab.ui.control.Label
        AlignmentModeCheckBox_2        matlab.ui.control.CheckBox
        LimitPositionButton_2          matlab.ui.control.Button
        LampChangeSetupPanel           matlab.ui.container.Panel
        HomePositionButton_2           matlab.ui.control.Button
        CurrentWavelengthEditField_2   matlab.ui.control.NumericEditField
        CurrentWavelengthEditField_2Label  matlab.ui.control.Label
        CurrentPositionEditField_2     matlab.ui.control.NumericEditField
        CurrentPositionEditField_2Label  matlab.ui.control.Label
        UpdateCurrentWavelengthButton_2  matlab.ui.control.Button
        UpdateCurrentPositionButton_2  matlab.ui.control.Button
        LampCheckONOFFPanel            matlab.ui.container.Panel
        EditField_5                    matlab.ui.control.EditField
        TungstenButton_2               matlab.ui.control.Button
        D2Button_2                     matlab.ui.control.Button
        TungstenONOFFPanel             matlab.ui.container.Panel
        EditField_4                    matlab.ui.control.EditField
        Switch_2                       matlab.ui.control.Switch
        D20NOFFPanel                   matlab.ui.container.Panel
        EditField_3                    matlab.ui.control.EditField
        Switch                         matlab.ui.control.Switch
        LampChangePanel                matlab.ui.container.Panel
        EditField_2                    matlab.ui.control.EditField
        TungstenButton                 matlab.ui.control.Button
        D2Button                       matlab.ui.control.Button
        GratingTab                     matlab.ui.container.Tab
        GratingSetupPanel              matlab.ui.container.Panel
        CurrentWavelengthEditField     matlab.ui.control.NumericEditField
        CurrentWavelengthEditFieldLabel  matlab.ui.control.Label
        UpdateCurrentWavelengthButton  matlab.ui.control.Button
        SaveStepsButton                matlab.ui.control.Button
        StartPositionEditField         matlab.ui.control.NumericEditField
        StartPositionLabel             matlab.ui.control.Label
        EndPositionEditField           matlab.ui.control.NumericEditField
        EndPositionEditFieldLabel      matlab.ui.control.Label
        MeasureNoEditField             matlab.ui.control.NumericEditField
        MeasureNoLabel                 matlab.ui.control.Label
        ReproductivityButton           matlab.ui.control.Button
        CurrentPositionEditField       matlab.ui.control.NumericEditField
        CurrentPositionLabel           matlab.ui.control.Label
        UpdateCurrentPositionButton    matlab.ui.control.Button
        AlignmentModeCheckBox          matlab.ui.control.CheckBox
        LimitPositionButton            matlab.ui.control.Button
        HomePositionButton             matlab.ui.control.Button
        SaveButton                     matlab.ui.control.Button
        HomePositionEditField          matlab.ui.control.NumericEditField
        HomePositionEditFieldLabel     matlab.ui.control.Label
        ReadingsTab                    matlab.ui.container.Tab
        PhotodetectorPanel             matlab.ui.container.Panel
        Slider                         matlab.ui.control.Slider
        SliderLabel                    matlab.ui.control.Label
        ChangeGainValuetoButton        matlab.ui.control.Button
        Button2                        matlab.ui.control.Button
        GainValueEditField             matlab.ui.control.NumericEditField
        GainValueEditFieldLabel        matlab.ui.control.Label
        SampleAmplifiedEditField       matlab.ui.control.NumericEditField
        SampleAmplifiedEditFieldLabel  matlab.ui.control.Label
        SampleEditField                matlab.ui.control.NumericEditField
        SampleEditFieldLabel           matlab.ui.control.Label
        ReferanceAmpifiedEditField     matlab.ui.control.NumericEditField
        ReferanceAmpifiedEditFieldLabel  matlab.ui.control.Label
        ReferanceEditField             matlab.ui.control.NumericEditField
        ReferanceEditFieldLabel        matlab.ui.control.Label
        GetValuesButton                matlab.ui.control.Button
        DateandTimePanel               matlab.ui.container.Panel
        TimeEditField                  matlab.ui.control.EditField
        TimeEditFieldLabel             matlab.ui.control.Label
        UpdateDateButton               matlab.ui.control.Button
        UpdateTimeButton               matlab.ui.control.Button
        DateDatePicker                 matlab.ui.control.DatePicker
        DateDatePickerLabel            matlab.ui.control.Label
        SuppliesVoltagesPanel          matlab.ui.container.Panel
        GetVoltagesButton              matlab.ui.control.Button
        VSupplyPanel_9                 matlab.ui.container.Panel
        VoltageEditField_9             matlab.ui.control.NumericEditField
        VoltageEditField_9Label        matlab.ui.control.Label
        VSupplyPanel_8                 matlab.ui.container.Panel
        VoltageEditField_8             matlab.ui.control.NumericEditField
        VoltageEditField_8Label        matlab.ui.control.Label
        VSupplyPanel_7                 matlab.ui.container.Panel
        VoltageEditField_7             matlab.ui.control.NumericEditField
        VoltageEditField_7Label        matlab.ui.control.Label
        VSupplyPanel_6                 matlab.ui.container.Panel
        VoltageEditField_6             matlab.ui.control.NumericEditField
        VoltageEditField_6Label        matlab.ui.control.Label
        VSupplyPanel                   matlab.ui.container.Panel
        VoltageEditField               matlab.ui.control.NumericEditField
        VoltageEditFieldLabel          matlab.ui.control.Label
        Panel                          matlab.ui.container.Panel
        RightPanel                     matlab.ui.container.Panel
        DisplayPanel                   matlab.ui.container.Panel
        PrintButton                    matlab.ui.control.Button
        SaveButton_2                   matlab.ui.control.Button
        ZoomoutButton                  matlab.ui.control.Button
        ZoominButton                   matlab.ui.control.Button
        YAxisButtonGroup               matlab.ui.container.ButtonGroup
        IntensityButton                matlab.ui.control.RadioButton
        AbsorbanceButton               matlab.ui.control.RadioButton
        XAxisButtonGroup               matlab.ui.container.ButtonGroup
        MotorStepButton                matlab.ui.control.RadioButton
        ClearChartButton               matlab.ui.control.Button
        StopButton                     matlab.ui.control.Button
        Button                         matlab.ui.control.Button
        ReadButton                     matlab.ui.control.Button
        Temp_DarkButton                matlab.ui.control.Button
        DarkButton                     matlab.ui.control.Button
        Sample2CheckBox                matlab.ui.control.CheckBox
        Referance2CheckBox             matlab.ui.control.CheckBox
        Sample1CheckBox                matlab.ui.control.CheckBox
        Referance1CheckBox             matlab.ui.control.CheckBox
        UIAxes                         matlab.ui.control.UIAxes
    end

    % Properties that correspond to apps with auto-reflow
    properties (Access = private)
        onePanelWidth = 576;
    end

    % Callbacks that handle component events
    methods (Access = private)

        % Button pushed function: D2Button
        function D2ButtonPushed(app, event)
        
            app.EditField_2.Value = "D2";
        end

        % Button pushed function: TungstenButton
        function TungstenButtonPushed(app, event)

            app.EditField_2.Value = "Tungsten";
        end

        % Value changed function: Switch
        function SwitchValueChanged(app, event)
            value = app.Switch.Value;
     if value == 'On'
             app.EditField_3.Value = "ON";
     end
        end

        % Changes arrangement of the app based on UIFigure width
        function updateAppLayout(app, event)
            currentFigureWidth = app.UIFigure.Position(3);
            if(currentFigureWidth <= app.onePanelWidth)
                % Change to a 2x1 grid
                app.GridLayout.RowHeight = {589, 589};
                app.GridLayout.ColumnWidth = {'1x'};
                app.RightPanel.Layout.Row = 2;
                app.RightPanel.Layout.Column = 1;
            else
                % Change to a 1x2 grid
                app.GridLayout.RowHeight = {'1x'};
                app.GridLayout.ColumnWidth = {447, '1x'};
                app.RightPanel.Layout.Row = 1;
                app.RightPanel.Layout.Column = 2;
            end
        end
    end

    % Component initialization
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Create UIFigure and hide until all components are created
            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.AutoResizeChildren = 'off';
            app.UIFigure.Position = [100 100 833 589];
            app.UIFigure.Name = 'MATLAB App';
            app.UIFigure.SizeChangedFcn = createCallbackFcn(app, @updateAppLayout, true);

            % Create GridLayout
            app.GridLayout = uigridlayout(app.UIFigure);
            app.GridLayout.ColumnWidth = {447, '1x'};
            app.GridLayout.RowHeight = {'1x'};
            app.GridLayout.ColumnSpacing = 0;
            app.GridLayout.RowSpacing = 0;
            app.GridLayout.Padding = [0 0 0 0];
            app.GridLayout.Scrollable = 'on';

            % Create LeftPanel
            app.LeftPanel = uipanel(app.GridLayout);
            app.LeftPanel.Layout.Row = 1;
            app.LeftPanel.Layout.Column = 1;

            % Create TabGroup
            app.TabGroup = uitabgroup(app.LeftPanel);
            app.TabGroup.Position = [1 15 432 567];

            % Create AlignmentTab
            app.AlignmentTab = uitab(app.TabGroup);
            app.AlignmentTab.Title = 'Alignment';

            % Create LampChangeSetupPanel
            app.LampChangeSetupPanel = uipanel(app.AlignmentTab);
            app.LampChangeSetupPanel.Title = '1. Lamp Change Setup';
            app.LampChangeSetupPanel.Position = [6 259 415 272];

            % Create LampChangePanel
            app.LampChangePanel = uipanel(app.LampChangeSetupPanel);
            app.LampChangePanel.Title = 'Lamp Change';
            app.LampChangePanel.Position = [10 176 190 69];

            % Create D2Button
            app.D2Button = uibutton(app.LampChangePanel, 'push');
            app.D2Button.ButtonPushedFcn = createCallbackFcn(app, @D2ButtonPushed, true);
            app.D2Button.Position = [5 15 34 22];
            app.D2Button.Text = 'D2';

            % Create TungstenButton
            app.TungstenButton = uibutton(app.LampChangePanel, 'push');
            app.TungstenButton.ButtonPushedFcn = createCallbackFcn(app, @TungstenButtonPushed, true);
            app.TungstenButton.Position = [45 15 59 22];
            app.TungstenButton.Text = 'Tungsten';

            % Create EditField_2
            app.EditField_2 = uieditfield(app.LampChangePanel, 'text');
            app.EditField_2.Position = [112 14 67 22];

            % Create D20NOFFPanel
            app.D20NOFFPanel = uipanel(app.LampChangeSetupPanel);
            app.D20NOFFPanel.Title = 'D2 0N/OFF';
            app.D20NOFFPanel.Position = [216 175 187 68];

            % Create Switch
            app.Switch = uiswitch(app.D20NOFFPanel, 'slider');
            app.Switch.ValueChangedFcn = createCallbackFcn(app, @SwitchValueChanged, true);
            app.Switch.Position = [33 15 45 20];

            % Create EditField_3
            app.EditField_3 = uieditfield(app.D20NOFFPanel, 'text');
            app.EditField_3.Position = [124 15 44 22];

            % Create TungstenONOFFPanel
            app.TungstenONOFFPanel = uipanel(app.LampChangeSetupPanel);
            app.TungstenONOFFPanel.Title = 'Tungsten ON/OFF';
            app.TungstenONOFFPanel.Position = [11 100 189 68];

            % Create Switch_2
            app.Switch_2 = uiswitch(app.TungstenONOFFPanel, 'slider');
            app.Switch_2.Position = [33 15 45 20];

            % Create EditField_4
            app.EditField_4 = uieditfield(app.TungstenONOFFPanel, 'text');
            app.EditField_4.Position = [128 16 41 22];

            % Create LampCheckONOFFPanel
            app.LampCheckONOFFPanel = uipanel(app.LampChangeSetupPanel);
            app.LampCheckONOFFPanel.Title = 'Lamp Check ON/OFF';
            app.LampCheckONOFFPanel.Position = [215 100 189 69];

            % Create D2Button_2
            app.D2Button_2 = uibutton(app.LampCheckONOFFPanel, 'push');
            app.D2Button_2.Position = [16 15 34 22];
            app.D2Button_2.Text = 'D2';

            % Create TungstenButton_2
            app.TungstenButton_2 = uibutton(app.LampCheckONOFFPanel, 'push');
            app.TungstenButton_2.Position = [55 15 59 22];
            app.TungstenButton_2.Text = 'Tungsten';

            % Create EditField_5
            app.EditField_5 = uieditfield(app.LampCheckONOFFPanel, 'text');
            app.EditField_5.Position = [128 15 44 22];

            % Create UpdateCurrentPositionButton_2
            app.UpdateCurrentPositionButton_2 = uibutton(app.LampChangeSetupPanel, 'push');
            app.UpdateCurrentPositionButton_2.Position = [12 65 139 22];
            app.UpdateCurrentPositionButton_2.Text = 'Update Current Position';

            % Create UpdateCurrentWavelengthButton_2
            app.UpdateCurrentWavelengthButton_2 = uibutton(app.LampChangeSetupPanel, 'push');
            app.UpdateCurrentWavelengthButton_2.Position = [12 39 164 22];
            app.UpdateCurrentWavelengthButton_2.Text = 'Update Current Wavelength';

            % Create CurrentPositionEditField_2Label
            app.CurrentPositionEditField_2Label = uilabel(app.LampChangeSetupPanel);
            app.CurrentPositionEditField_2Label.HorizontalAlignment = 'right';
            app.CurrentPositionEditField_2Label.Position = [187 64 98 22];
            app.CurrentPositionEditField_2Label.Text = 'Current Position :';

            % Create CurrentPositionEditField_2
            app.CurrentPositionEditField_2 = uieditfield(app.LampChangeSetupPanel, 'numeric');
            app.CurrentPositionEditField_2.Position = [310 64 40 22];

            % Create CurrentWavelengthEditField_2Label
            app.CurrentWavelengthEditField_2Label = uilabel(app.LampChangeSetupPanel);
            app.CurrentWavelengthEditField_2Label.HorizontalAlignment = 'right';
            app.CurrentWavelengthEditField_2Label.Position = [187 37 115 22];
            app.CurrentWavelengthEditField_2Label.Text = 'Current Wavelength:';

            % Create CurrentWavelengthEditField_2
            app.CurrentWavelengthEditField_2 = uieditfield(app.LampChangeSetupPanel, 'numeric');
            app.CurrentWavelengthEditField_2.Position = [310 40 41 22];

            % Create HomePositionButton_2
            app.HomePositionButton_2 = uibutton(app.LampChangeSetupPanel, 'push');
            app.HomePositionButton_2.Position = [111 8 120 22];
            app.HomePositionButton_2.Text = 'Home Position';

            % Create FilterSetupPanel
            app.FilterSetupPanel = uipanel(app.AlignmentTab);
            app.FilterSetupPanel.Title = '2. Filter Setup';
            app.FilterSetupPanel.Position = [10 25 410 215];

            % Create LimitPositionButton_2
            app.LimitPositionButton_2 = uibutton(app.FilterSetupPanel, 'push');
            app.LimitPositionButton_2.Position = [6 164 83 22];
            app.LimitPositionButton_2.Text = 'Limit Position';

            % Create AlignmentModeCheckBox_2
            app.AlignmentModeCheckBox_2 = uicheckbox(app.FilterSetupPanel);
            app.AlignmentModeCheckBox_2.Text = 'Alignment Mode';
            app.AlignmentModeCheckBox_2.Position = [111 164 109 22];

            % Create CurrentPositionEditField_3Label
            app.CurrentPositionEditField_3Label = uilabel(app.FilterSetupPanel);
            app.CurrentPositionEditField_3Label.HorizontalAlignment = 'right';
            app.CurrentPositionEditField_3Label.Position = [259 164 98 22];
            app.CurrentPositionEditField_3Label.Text = 'Current Position :';

            % Create CurrentPositionEditField_3
            app.CurrentPositionEditField_3 = uieditfield(app.FilterSetupPanel, 'numeric');
            app.CurrentPositionEditField_3.Position = [359 164 40 22];

            % Create UpdateCurrentPositionButton_3
            app.UpdateCurrentPositionButton_3 = uibutton(app.FilterSetupPanel, 'push');
            app.UpdateCurrentPositionButton_3.Position = [9 130 139 22];
            app.UpdateCurrentPositionButton_3.Text = 'Update Current Position';

            % Create UpdateCurrentWavelengthButton_3
            app.UpdateCurrentWavelengthButton_3 = uibutton(app.FilterSetupPanel, 'push');
            app.UpdateCurrentWavelengthButton_3.Position = [9 99 164 22];
            app.UpdateCurrentWavelengthButton_3.Text = 'Update Current Wavelength';

            % Create CurrentPositionEditField_4Label
            app.CurrentPositionEditField_4Label = uilabel(app.FilterSetupPanel);
            app.CurrentPositionEditField_4Label.HorizontalAlignment = 'right';
            app.CurrentPositionEditField_4Label.Position = [237 130 98 22];
            app.CurrentPositionEditField_4Label.Text = 'Current Position :';

            % Create CurrentPositionEditField_4
            app.CurrentPositionEditField_4 = uieditfield(app.FilterSetupPanel, 'numeric');
            app.CurrentPositionEditField_4.Position = [360 130 40 22];

            % Create CurrentWavelengthEditField_3Label
            app.CurrentWavelengthEditField_3Label = uilabel(app.FilterSetupPanel);
            app.CurrentWavelengthEditField_3Label.HorizontalAlignment = 'right';
            app.CurrentWavelengthEditField_3Label.Position = [237 96 115 22];
            app.CurrentWavelengthEditField_3Label.Text = 'Current Wavelength:';

            % Create CurrentWavelengthEditField_3
            app.CurrentWavelengthEditField_3 = uieditfield(app.FilterSetupPanel, 'numeric');
            app.CurrentWavelengthEditField_3.Position = [360 99 41 22];

            % Create MoveMotortostepNoEditFieldLabel
            app.MoveMotortostepNoEditFieldLabel = uilabel(app.FilterSetupPanel);
            app.MoveMotortostepNoEditFieldLabel.HorizontalAlignment = 'right';
            app.MoveMotortostepNoEditFieldLabel.Position = [11 60 133 22];
            app.MoveMotortostepNoEditFieldLabel.Text = 'Move Motor to step No.:';

            % Create MoveMotortostepNoEditField
            app.MoveMotortostepNoEditField = uieditfield(app.FilterSetupPanel, 'numeric');
            app.MoveMotortostepNoEditField.Position = [154 58 42 25];

            % Create MoveButton
            app.MoveButton = uibutton(app.FilterSetupPanel, 'push');
            app.MoveButton.Position = [210 59 77 22];
            app.MoveButton.Text = 'Move';

            % Create HomePositionButton_3
            app.HomePositionButton_3 = uibutton(app.FilterSetupPanel, 'push');
            app.HomePositionButton_3.Position = [34 16 120 22];
            app.HomePositionButton_3.Text = 'Home Position';

            % Create SaveCalibrationButton
            app.SaveCalibrationButton = uibutton(app.FilterSetupPanel, 'push');
            app.SaveCalibrationButton.Position = [178 16 120 22];
            app.SaveCalibrationButton.Text = 'Save Calibration';

            % Create GratingTab
            app.GratingTab = uitab(app.TabGroup);
            app.GratingTab.Title = 'Grating';

            % Create GratingSetupPanel
            app.GratingSetupPanel = uipanel(app.GratingTab);
            app.GratingSetupPanel.Title = '1.Grating Setup';
            app.GratingSetupPanel.Position = [18 160 402 344];

            % Create HomePositionEditFieldLabel
            app.HomePositionEditFieldLabel = uilabel(app.GratingSetupPanel);
            app.HomePositionEditFieldLabel.HorizontalAlignment = 'right';
            app.HomePositionEditFieldLabel.Position = [10 281 84 22];
            app.HomePositionEditFieldLabel.Text = 'Home Position';

            % Create HomePositionEditField
            app.HomePositionEditField = uieditfield(app.GratingSetupPanel, 'numeric');
            app.HomePositionEditField.Position = [109 281 31 22];

            % Create SaveButton
            app.SaveButton = uibutton(app.GratingSetupPanel, 'push');
            app.SaveButton.Position = [162 281 43 22];
            app.SaveButton.Text = 'Save';

            % Create HomePositionButton
            app.HomePositionButton = uibutton(app.GratingSetupPanel, 'push');
            app.HomePositionButton.Position = [229 281 94 22];
            app.HomePositionButton.Text = 'Home Position';

            % Create LimitPositionButton
            app.LimitPositionButton = uibutton(app.GratingSetupPanel, 'push');
            app.LimitPositionButton.Position = [14 238 100 22];
            app.LimitPositionButton.Text = 'Limit Position';

            % Create AlignmentModeCheckBox
            app.AlignmentModeCheckBox = uicheckbox(app.GratingSetupPanel);
            app.AlignmentModeCheckBox.Text = 'Alignment Mode';
            app.AlignmentModeCheckBox.Position = [145 236 109 22];

            % Create UpdateCurrentPositionButton
            app.UpdateCurrentPositionButton = uibutton(app.GratingSetupPanel, 'push');
            app.UpdateCurrentPositionButton.Position = [7 196 139 22];
            app.UpdateCurrentPositionButton.Text = 'Update Current Position';

            % Create CurrentPositionLabel
            app.CurrentPositionLabel = uilabel(app.GratingSetupPanel);
            app.CurrentPositionLabel.HorizontalAlignment = 'right';
            app.CurrentPositionLabel.Position = [187 196 98 22];
            app.CurrentPositionLabel.Text = 'Current Position :';

            % Create CurrentPositionEditField
            app.CurrentPositionEditField = uieditfield(app.GratingSetupPanel, 'numeric');
            app.CurrentPositionEditField.Position = [310 196 40 22];

            % Create ReproductivityButton
            app.ReproductivityButton = uibutton(app.GratingSetupPanel, 'push');
            app.ReproductivityButton.Position = [12 100 136 22];
            app.ReproductivityButton.Text = 'Reproductivity';

            % Create MeasureNoLabel
            app.MeasureNoLabel = uilabel(app.GratingSetupPanel);
            app.MeasureNoLabel.HorizontalAlignment = 'right';
            app.MeasureNoLabel.Position = [187 100 91 22];
            app.MeasureNoLabel.Text = 'Measure No. :';

            % Create MeasureNoEditField
            app.MeasureNoEditField = uieditfield(app.GratingSetupPanel, 'numeric');
            app.MeasureNoEditField.Position = [308 100 43 22];

            % Create EndPositionEditFieldLabel
            app.EndPositionEditFieldLabel = uilabel(app.GratingSetupPanel);
            app.EndPositionEditFieldLabel.HorizontalAlignment = 'right';
            app.EndPositionEditFieldLabel.Position = [200 58 83 22];
            app.EndPositionEditFieldLabel.Text = 'End Position :';

            % Create EndPositionEditField
            app.EndPositionEditField = uieditfield(app.GratingSetupPanel, 'numeric');
            app.EndPositionEditField.Position = [311 58 40 22];

            % Create StartPositionLabel
            app.StartPositionLabel = uilabel(app.GratingSetupPanel);
            app.StartPositionLabel.HorizontalAlignment = 'right';
            app.StartPositionLabel.Position = [14 61 80 22];
            app.StartPositionLabel.Text = 'Start Position:';

            % Create StartPositionEditField
            app.StartPositionEditField = uieditfield(app.GratingSetupPanel, 'numeric');
            app.StartPositionEditField.Position = [106 61 39 22];

            % Create SaveStepsButton
            app.SaveStepsButton = uibutton(app.GratingSetupPanel, 'push');
            app.SaveStepsButton.Position = [152 18 71 22];
            app.SaveStepsButton.Text = 'Save Steps';

            % Create UpdateCurrentWavelengthButton
            app.UpdateCurrentWavelengthButton = uibutton(app.GratingSetupPanel, 'push');
            app.UpdateCurrentWavelengthButton.Position = [4 163 164 22];
            app.UpdateCurrentWavelengthButton.Text = 'Update Current Wavelength';

            % Create CurrentWavelengthEditFieldLabel
            app.CurrentWavelengthEditFieldLabel = uilabel(app.GratingSetupPanel);
            app.CurrentWavelengthEditFieldLabel.HorizontalAlignment = 'right';
            app.CurrentWavelengthEditFieldLabel.Position = [187 162 115 22];
            app.CurrentWavelengthEditFieldLabel.Text = 'Current Wavelength:';

            % Create CurrentWavelengthEditField
            app.CurrentWavelengthEditField = uieditfield(app.GratingSetupPanel, 'numeric');
            app.CurrentWavelengthEditField.Position = [310 165 41 22];

            % Create ReadingsTab
            app.ReadingsTab = uitab(app.TabGroup);
            app.ReadingsTab.Title = 'Readings';

            % Create Panel
            app.Panel = uipanel(app.ReadingsTab);
            app.Panel.Title = 'Panel';
            app.Panel.Position = [1 374 2 2];

            % Create SuppliesVoltagesPanel
            app.SuppliesVoltagesPanel = uipanel(app.ReadingsTab);
            app.SuppliesVoltagesPanel.Title = '2. Supplies Voltages';
            app.SuppliesVoltagesPanel.Position = [16 246 397 171];

            % Create VSupplyPanel
            app.VSupplyPanel = uipanel(app.SuppliesVoltagesPanel);
            app.VSupplyPanel.Title = '+12V Supply';
            app.VSupplyPanel.Position = [11 82 108 61];

            % Create VoltageEditFieldLabel
            app.VoltageEditFieldLabel = uilabel(app.VSupplyPanel);
            app.VoltageEditFieldLabel.HorizontalAlignment = 'right';
            app.VoltageEditFieldLabel.Position = [7 12 41 22];
            app.VoltageEditFieldLabel.Text = 'Voltage';

            % Create VoltageEditField
            app.VoltageEditField = uieditfield(app.VSupplyPanel, 'numeric');
            app.VoltageEditField.Position = [62 12 26 22];

            % Create VSupplyPanel_6
            app.VSupplyPanel_6 = uipanel(app.SuppliesVoltagesPanel);
            app.VSupplyPanel_6.Title = '-12V Supply';
            app.VSupplyPanel_6.Position = [144 83 108 61];

            % Create VoltageEditField_6Label
            app.VoltageEditField_6Label = uilabel(app.VSupplyPanel_6);
            app.VoltageEditField_6Label.HorizontalAlignment = 'right';
            app.VoltageEditField_6Label.Position = [7 12 41 22];
            app.VoltageEditField_6Label.Text = 'Voltage';

            % Create VoltageEditField_6
            app.VoltageEditField_6 = uieditfield(app.VSupplyPanel_6, 'numeric');
            app.VoltageEditField_6.Position = [62 12 26 22];

            % Create VSupplyPanel_7
            app.VSupplyPanel_7 = uipanel(app.SuppliesVoltagesPanel);
            app.VSupplyPanel_7.Title = '12V Supply';
            app.VSupplyPanel_7.Position = [271 83 108 61];

            % Create VoltageEditField_7Label
            app.VoltageEditField_7Label = uilabel(app.VSupplyPanel_7);
            app.VoltageEditField_7Label.HorizontalAlignment = 'right';
            app.VoltageEditField_7Label.Position = [7 12 41 22];
            app.VoltageEditField_7Label.Text = 'Voltage';

            % Create VoltageEditField_7
            app.VoltageEditField_7 = uieditfield(app.VSupplyPanel_7, 'numeric');
            app.VoltageEditField_7.Position = [62 12 26 22];

            % Create VSupplyPanel_8
            app.VSupplyPanel_8 = uipanel(app.SuppliesVoltagesPanel);
            app.VSupplyPanel_8.Title = '5V Supply';
            app.VSupplyPanel_8.Position = [11 13 108 61];

            % Create VoltageEditField_8Label
            app.VoltageEditField_8Label = uilabel(app.VSupplyPanel_8);
            app.VoltageEditField_8Label.HorizontalAlignment = 'right';
            app.VoltageEditField_8Label.Position = [7 12 41 22];
            app.VoltageEditField_8Label.Text = 'Voltage';

            % Create VoltageEditField_8
            app.VoltageEditField_8 = uieditfield(app.VSupplyPanel_8, 'numeric');
            app.VoltageEditField_8.Position = [62 12 26 22];

            % Create VSupplyPanel_9
            app.VSupplyPanel_9 = uipanel(app.SuppliesVoltagesPanel);
            app.VSupplyPanel_9.Title = '3.3V Supply';
            app.VSupplyPanel_9.Position = [148 14 108 61];

            % Create VoltageEditField_9Label
            app.VoltageEditField_9Label = uilabel(app.VSupplyPanel_9);
            app.VoltageEditField_9Label.HorizontalAlignment = 'right';
            app.VoltageEditField_9Label.Position = [7 12 41 22];
            app.VoltageEditField_9Label.Text = 'Voltage';

            % Create VoltageEditField_9
            app.VoltageEditField_9 = uieditfield(app.VSupplyPanel_9, 'numeric');
            app.VoltageEditField_9.Position = [62 12 26 22];

            % Create GetVoltagesButton
            app.GetVoltagesButton = uibutton(app.SuppliesVoltagesPanel, 'push');
            app.GetVoltagesButton.Position = [284 30 90 28];
            app.GetVoltagesButton.Text = 'Get Voltages';

            % Create DateandTimePanel
            app.DateandTimePanel = uipanel(app.ReadingsTab);
            app.DateandTimePanel.Title = '1. Date and Time';
            app.DateandTimePanel.Position = [16 427 398 100];

            % Create DateDatePickerLabel
            app.DateDatePickerLabel = uilabel(app.DateandTimePanel);
            app.DateDatePickerLabel.HorizontalAlignment = 'right';
            app.DateDatePickerLabel.Position = [24 45 31 22];
            app.DateDatePickerLabel.Text = 'Date';

            % Create DateDatePicker
            app.DateDatePicker = uidatepicker(app.DateandTimePanel);
            app.DateDatePicker.Position = [70 45 128 22];

            % Create UpdateTimeButton
            app.UpdateTimeButton = uibutton(app.DateandTimePanel, 'push');
            app.UpdateTimeButton.Position = [267 15 77 22];
            app.UpdateTimeButton.Text = 'Update Time';

            % Create UpdateDateButton
            app.UpdateDateButton = uibutton(app.DateandTimePanel, 'push');
            app.UpdateDateButton.Position = [265 45 79 22];
            app.UpdateDateButton.Text = 'Update Date';

            % Create TimeEditFieldLabel
            app.TimeEditFieldLabel = uilabel(app.DateandTimePanel);
            app.TimeEditFieldLabel.HorizontalAlignment = 'right';
            app.TimeEditFieldLabel.Position = [24 13 32 22];
            app.TimeEditFieldLabel.Text = 'Time';

            % Create TimeEditField
            app.TimeEditField = uieditfield(app.DateandTimePanel, 'text');
            app.TimeEditField.Position = [71 13 123 22];

            % Create PhotodetectorPanel
            app.PhotodetectorPanel = uipanel(app.ReadingsTab);
            app.PhotodetectorPanel.Title = '3. Photodetector';
            app.PhotodetectorPanel.Position = [18 24 397 210];

            % Create GetValuesButton
            app.GetValuesButton = uibutton(app.PhotodetectorPanel, 'push');
            app.GetValuesButton.Position = [245 84 90 28];
            app.GetValuesButton.Text = 'Get Values';

            % Create ReferanceEditFieldLabel
            app.ReferanceEditFieldLabel = uilabel(app.PhotodetectorPanel);
            app.ReferanceEditFieldLabel.HorizontalAlignment = 'right';
            app.ReferanceEditFieldLabel.Position = [21 157 64 22];
            app.ReferanceEditFieldLabel.Text = 'Referance ';

            % Create ReferanceEditField
            app.ReferanceEditField = uieditfield(app.PhotodetectorPanel, 'numeric');
            app.ReferanceEditField.Position = [100 157 86 21];

            % Create ReferanceAmpifiedEditFieldLabel
            app.ReferanceAmpifiedEditFieldLabel = uilabel(app.PhotodetectorPanel);
            app.ReferanceAmpifiedEditFieldLabel.HorizontalAlignment = 'right';
            app.ReferanceAmpifiedEditFieldLabel.Position = [190 155 110 22];
            app.ReferanceAmpifiedEditFieldLabel.Text = 'Referance Ampified';

            % Create ReferanceAmpifiedEditField
            app.ReferanceAmpifiedEditField = uieditfield(app.PhotodetectorPanel, 'numeric');
            app.ReferanceAmpifiedEditField.Position = [303 154 86 21];

            % Create SampleEditFieldLabel
            app.SampleEditFieldLabel = uilabel(app.PhotodetectorPanel);
            app.SampleEditFieldLabel.HorizontalAlignment = 'right';
            app.SampleEditFieldLabel.Position = [24 124 46 22];
            app.SampleEditFieldLabel.Text = 'Sample';

            % Create SampleEditField
            app.SampleEditField = uieditfield(app.PhotodetectorPanel, 'numeric');
            app.SampleEditField.Position = [100 124 85 21];

            % Create SampleAmplifiedEditFieldLabel
            app.SampleAmplifiedEditFieldLabel = uilabel(app.PhotodetectorPanel);
            app.SampleAmplifiedEditFieldLabel.HorizontalAlignment = 'right';
            app.SampleAmplifiedEditFieldLabel.Position = [195 123 98 22];
            app.SampleAmplifiedEditFieldLabel.Text = 'Sample Amplified';

            % Create SampleAmplifiedEditField
            app.SampleAmplifiedEditField = uieditfield(app.PhotodetectorPanel, 'numeric');
            app.SampleAmplifiedEditField.Position = [302 122 85 21];

            % Create GainValueEditFieldLabel
            app.GainValueEditFieldLabel = uilabel(app.PhotodetectorPanel);
            app.GainValueEditFieldLabel.HorizontalAlignment = 'right';
            app.GainValueEditFieldLabel.Position = [8 91 64 22];
            app.GainValueEditFieldLabel.Text = 'Gain Value';

            % Create GainValueEditField
            app.GainValueEditField = uieditfield(app.PhotodetectorPanel, 'numeric');
            app.GainValueEditField.Position = [102 91 85 21];

            % Create Button2
            app.Button2 = uibutton(app.PhotodetectorPanel, 'push');
            app.Button2.Position = [1 207 2 2];
            app.Button2.Text = 'Button2';

            % Create ChangeGainValuetoButton
            app.ChangeGainValuetoButton = uibutton(app.PhotodetectorPanel, 'push');
            app.ChangeGainValuetoButton.Position = [14 32 153 28];
            app.ChangeGainValuetoButton.Text = 'Change Gain Value to';

            % Create SliderLabel
            app.SliderLabel = uilabel(app.PhotodetectorPanel);
            app.SliderLabel.HorizontalAlignment = 'right';
            app.SliderLabel.Position = [191 38 36 22];
            app.SliderLabel.Text = 'Slider';

            % Create Slider
            app.Slider = uislider(app.PhotodetectorPanel);
            app.Slider.Position = [248 47 92 10];

            % Create RightPanel
            app.RightPanel = uipanel(app.GridLayout);
            app.RightPanel.Layout.Row = 1;
            app.RightPanel.Layout.Column = 2;

            % Create DisplayPanel
            app.DisplayPanel = uipanel(app.RightPanel);
            app.DisplayPanel.Title = 'Display';
            app.DisplayPanel.Position = [7 19 372 562];

            % Create UIAxes
            app.UIAxes = uiaxes(app.DisplayPanel);
            title(app.UIAxes, 'Title')
            xlabel(app.UIAxes, {'Motor Step'; ''})
            ylabel(app.UIAxes, {'Intensity'; ''})
            zlabel(app.UIAxes, 'Z')
            app.UIAxes.XColor = [0.149 0.149 0.149];
            app.UIAxes.XTickLabel = {'0'; '5000'; '10000'; '15000'; '20000'; '25000'; '30000'; '35000'; '40000'};
            app.UIAxes.YTickLabel = {'0'; '10000'; '20000'; '30000'; '40000'; '50000'; '60000'; '70000'; '80000'};
            app.UIAxes.XMinorGrid = 'on';
            app.UIAxes.YMinorGrid = 'on';
            app.UIAxes.GridColor = [0 0 0];
            app.UIAxes.GridAlpha = 0.15;
            app.UIAxes.Position = [3 175 263 323];

            % Create Referance1CheckBox
            app.Referance1CheckBox = uicheckbox(app.DisplayPanel);
            app.Referance1CheckBox.Text = 'Referance 1';
            app.Referance1CheckBox.Position = [263 456 88 22];

            % Create Sample1CheckBox
            app.Sample1CheckBox = uicheckbox(app.DisplayPanel);
            app.Sample1CheckBox.Text = 'Sample 1';
            app.Sample1CheckBox.Position = [263 423 73 22];

            % Create Referance2CheckBox
            app.Referance2CheckBox = uicheckbox(app.DisplayPanel);
            app.Referance2CheckBox.Text = 'Referance 2';
            app.Referance2CheckBox.Position = [263 391 88 22];

            % Create Sample2CheckBox
            app.Sample2CheckBox = uicheckbox(app.DisplayPanel);
            app.Sample2CheckBox.Text = 'Sample 2';
            app.Sample2CheckBox.Position = [263 356 73 22];

            % Create DarkButton
            app.DarkButton = uibutton(app.DisplayPanel, 'push');
            app.DarkButton.Position = [6 131 49 22];
            app.DarkButton.Text = 'Dark';

            % Create Temp_DarkButton
            app.Temp_DarkButton = uibutton(app.DisplayPanel, 'push');
            app.Temp_DarkButton.Position = [76 131 71 22];
            app.Temp_DarkButton.Text = 'Temp_Dark';

            % Create ReadButton
            app.ReadButton = uibutton(app.DisplayPanel, 'push');
            app.ReadButton.Position = [166 130 43 22];
            app.ReadButton.Text = 'Read';

            % Create Button
            app.Button = uibutton(app.DisplayPanel, 'push');
            app.Button.Position = [193 164 2 2];

            % Create StopButton
            app.StopButton = uibutton(app.DisplayPanel, 'push');
            app.StopButton.Position = [220 130 45 22];
            app.StopButton.Text = 'Stop';

            % Create ClearChartButton
            app.ClearChartButton = uibutton(app.DisplayPanel, 'push');
            app.ClearChartButton.Position = [290 130 80 22];
            app.ClearChartButton.Text = 'Clear Chart';

            % Create XAxisButtonGroup
            app.XAxisButtonGroup = uibuttongroup(app.DisplayPanel);
            app.XAxisButtonGroup.Title = 'X Axis';
            app.XAxisButtonGroup.Position = [6 58 168 47];

            % Create MotorStepButton
            app.MotorStepButton = uiradiobutton(app.XAxisButtonGroup);
            app.MotorStepButton.Text = 'Motor Step';
            app.MotorStepButton.Position = [11 1 81 22];
            app.MotorStepButton.Value = true;

            % Create YAxisButtonGroup
            app.YAxisButtonGroup = uibuttongroup(app.DisplayPanel);
            app.YAxisButtonGroup.Title = 'Y Axis';
            app.YAxisButtonGroup.Position = [186 60 183 48];

            % Create AbsorbanceButton
            app.AbsorbanceButton = uiradiobutton(app.YAxisButtonGroup);
            app.AbsorbanceButton.Text = 'Absorbance';
            app.AbsorbanceButton.Position = [13 1 86 22];
            app.AbsorbanceButton.Value = true;

            % Create IntensityButton
            app.IntensityButton = uiradiobutton(app.YAxisButtonGroup);
            app.IntensityButton.Text = 'Intensity';
            app.IntensityButton.Position = [109 2 67 22];

            % Create ZoominButton
            app.ZoominButton = uibutton(app.DisplayPanel, 'push');
            app.ZoominButton.Position = [6 506 59 22];
            app.ZoominButton.Text = 'Zoom in';

            % Create ZoomoutButton
            app.ZoomoutButton = uibutton(app.DisplayPanel, 'push');
            app.ZoomoutButton.Position = [73 506 66 22];
            app.ZoomoutButton.Text = 'Zoom out';

            % Create SaveButton_2
            app.SaveButton_2 = uibutton(app.DisplayPanel, 'push');
            app.SaveButton_2.Position = [157 506 59 22];
            app.SaveButton_2.Text = 'Save';

            % Create PrintButton
            app.PrintButton = uibutton(app.DisplayPanel, 'push');
            app.PrintButton.Position = [233 506 59 22];
            app.PrintButton.Text = 'Print';

            % Show the figure after all components are created
            app.UIFigure.Visible = 'on';
        end
    end

    % App creation and deletion
    methods (Access = public)

        % Construct app
        function app = app1

            % Create UIFigure and components
            createComponents(app)

            % Register the app with App Designer
            registerApp(app, app.UIFigure)

            if nargout == 0
                clear app
            end
        end

        % Code that executes before app deletion
        function delete(app)

            % Delete UIFigure when app is deleted
            delete(app.UIFigure)
        end
    end
end
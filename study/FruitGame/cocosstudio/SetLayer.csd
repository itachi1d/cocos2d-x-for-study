<GameFile>
  <PropertyGroup Name="SetLayer" Type="Scene" ID="0c69a01e-ac09-47e8-9598-5ddbf734ca51" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="22" ctype="GameNodeObjectData">
        <Size X="540.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="night_1" ActionTag="-1262492919" Tag="23" IconVisible="False" ctype="SpriteObjectData">
            <Size X="540.0000" Y="720.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="pic/night.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="setBack_2" ActionTag="1732158063" Tag="24" IconVisible="False" LeftMargin="70.3122" RightMargin="69.6878" TopMargin="228.5963" BottomMargin="191.4037" ctype="SpriteObjectData">
            <Size X="400.0000" Y="300.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="270.3122" Y="341.4037" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5006" Y="0.4742" />
            <PreSize X="0.7407" Y="0.4167" />
            <FileData Type="Normal" Path="pic/setBack.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="sound_1" ActionTag="-916334477" Tag="17" IconVisible="False" LeftMargin="105.7736" RightMargin="294.2264" TopMargin="347.7355" BottomMargin="282.2645" ctype="SpriteObjectData">
            <Size X="140.0000" Y="90.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="175.7736" Y="327.2645" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.3255" Y="0.4545" />
            <PreSize X="0.2593" Y="0.1250" />
            <FileData Type="Normal" Path="pic/sound.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="music_2" ActionTag="-1868073114" Tag="18" IconVisible="False" LeftMargin="102.7358" RightMargin="287.2642" TopMargin="260.7922" BottomMargin="369.2078" ctype="SpriteObjectData">
            <Size X="150.0000" Y="90.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="177.7358" Y="414.2078" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.3291" Y="0.5753" />
            <PreSize X="0.2778" Y="0.1250" />
            <FileData Type="Normal" Path="pic/music.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="menu_btn" ActionTag="310348431" Tag="19" IconVisible="False" LeftMargin="213.8057" RightMargin="226.1943" TopMargin="435.9665" BottomMargin="209.0335" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="53" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="100.0000" Y="75.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="263.8057" Y="246.5335" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4885" Y="0.3424" />
            <PreSize X="0.1852" Y="0.1042" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="button/menu_off.png" Plist="" />
            <NormalFileData Type="Normal" Path="button/menu.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="music_btn" ActionTag="-252146191" Tag="22" IconVisible="False" LeftMargin="340.3085" RightMargin="135.6915" TopMargin="278.9705" BottomMargin="377.0295" TouchEnable="True" ctype="CheckBoxObjectData">
            <Size X="64.0000" Y="64.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="372.3085" Y="409.0295" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.6895" Y="0.5681" />
            <PreSize X="0.1185" Y="0.0889" />
            <NormalBackFileData Type="Normal" Path="button/sound_on.png" Plist="" />
            <PressedBackFileData Type="Normal" Path="button/sound_stop.png" Plist="" />
            <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
            <NodeNormalFileData Type="Normal" Path="button/sound_off.png" Plist="" />
            <NodeDisableFileData Type="Normal" Path="button/sound_on.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="sound_btn" ActionTag="-19438657" CallBackType="Touch" Tag="23" IconVisible="False" LeftMargin="339.2886" RightMargin="136.7114" TopMargin="365.7250" BottomMargin="290.2750" TouchEnable="True" ctype="CheckBoxObjectData">
            <Size X="64.0000" Y="64.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="371.2886" Y="322.2750" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.6876" Y="0.4476" />
            <PreSize X="0.1185" Y="0.0889" />
            <NormalBackFileData Type="Normal" Path="button/sound_on.png" Plist="" />
            <PressedBackFileData Type="Normal" Path="button/sound_stop.png" Plist="" />
            <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
            <NodeNormalFileData Type="Normal" Path="button/sound_off.png" Plist="" />
            <NodeDisableFileData Type="Normal" Path="button/sound_off.png" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>
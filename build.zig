const std = @import("std");

const ExampleCase = struct {
    name: []const u8,
    file: []const u8,
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const examples = [_]ExampleCase{
        .{ .name = "extest", .file = "src/extest.c" },
        .{ .name = "ch3-1", .file = "src/ch3-1.c" },
        .{ .name = "ch4-1", .file = "src/ch4-1.c" },
        .{ .name = "ch4-2", .file = "src/ch4-2.c" },
        .{ .name = "ch5-1", .file = "src/ch5-1.c" },
        .{ .name = "ch5-2", .file = "src/ch5-2.c" },
        .{ .name = "ch5-3", .file = "src/ch5-3.c" },
        .{ .name = "ch5-4", .file = "src/ch5-4.c" },
        .{ .name = "ch5-5", .file = "src/ch5-5.c" },
        .{ .name = "ch5-6", .file = "src/ch5-6.c" },
        .{ .name = "ch5-7", .file = "src/ch5-7.c" },
    };

    for (examples) |ex| {
        const exe = b.addExecutable(.{
            .name = ex.name,
            .target = target,
            .optimize = optimize,
        });
        exe.addCSourceFiles(.{
            .files = &.{ex.file},
        });
        b.installArtifact(exe);
        exe.linkLibC();

        const run_cmd = b.addRunArtifact(exe);

        run_cmd.step.dependOn(b.getInstallStep());

        if (b.args) |args| {
            run_cmd.addArgs(args);
        }

        const run_step = b.step(ex.name, "Run the example");
        run_step.dependOn(&run_cmd.step);
    }
}
